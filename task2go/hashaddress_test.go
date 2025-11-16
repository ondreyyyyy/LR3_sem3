package main

import (
	"strconv"
	"testing"
)

func TestNewHashATable(t *testing.T) {
	t.Run("Создание хэш-таблицы с открытой адресацией", func(t *testing.T) {
		hash := NewHashATable()
		if hash == nil {
			t.Error("Конструктор вернул nil")
		}
		if hash.capacity != 8 {
			t.Errorf("Ожидалась емкость 8, получено %d", hash.capacity)
		}
		if hash.size != 0 {
			t.Errorf("Ожидался размер 0, получено %d", hash.size)
		}
		if len(hash.table) != 8 {
			t.Error("Таблица не инициализирована корректно")
		}

		// Проверяем инициализацию ячеек
		for i := 0; i < hash.capacity; i++ {
			if !hash.table[i].isEmpty || hash.table[i].isDeleted {
				t.Error("Ячейки не инициализированы корректно")
			}
		}
	})
}

func TestHashA_hashaFunc(t *testing.T) {
	hash := NewHashATable()

	t.Run("Хэш-функция возвращает корректный диапазон", func(t *testing.T) {
		key := "test_key"
		hashValue := hash.hashaFunc(key)

		if hashValue < 0 || hashValue >= hash.capacity {
			t.Errorf("Хэш %d выходит за границы таблицы [0, %d]", hashValue, hash.capacity-1)
		}
	})

	t.Run("Детерминированность хэш-функции", func(t *testing.T) {
		key := "одинаковый_ключ"
		hash1 := hash.hashaFunc(key)
		hash2 := hash.hashaFunc(key)

		if hash1 != hash2 {
			t.Error("Хэш-функция не детерминирована")
		}
	})
}

func TestHashA_AddElement(t *testing.T) {
	hash := NewHashATable()

	t.Run("Добавление нового элемента", func(t *testing.T) {
		hash.AddElement("ключ1", "значение1")
		if hash.size != 1 {
			t.Errorf("Ожидался размер 1, получено %d", hash.size)
		}

		result := hash.FindElementStr("ключ1")
		if result != "значение1" {
			t.Errorf("Ожидалось 'значение1', получено '%s'", result)
		}
	})

	t.Run("Обновление существующего элемента", func(t *testing.T) {
		hash.AddElement("ключ1", "новое_значение")
		if hash.size != 1 {
			t.Error("Размер не должен меняться при обновлении")
		}

		result := hash.FindElementStr("ключ1")
		if result != "новое_значение" {
			t.Errorf("Ожидалось 'новое_значение' после обновления, получено '%s'", result)
		}
	})

	t.Run("Обработка коллизий", func(t *testing.T) {
		// Добавляем элементы, которые могут вызвать коллизии
		hash.AddElement("коллизия1", "значение1")
		hash.AddElement("коллизия2", "значение2")
		hash.AddElement("коллизия3", "значение3")

		if hash.size != 4 {
			t.Errorf("Ожидался размер 4, получено %d", hash.size)
		}
	})

	t.Run("Автоматическое рехэширование", func(t *testing.T) {
		// Заполняем таблицу до порога рехэширования
		for i := 0; i < 10; i++ {
			hash.AddElement("ключ"+strconv.Itoa(i), "значение"+strconv.Itoa(i))
		}
		// Должно произойти рехэширование
		if hash.capacity <= 8 {
			t.Error("Рехэширование не произошло")
		}
	})
}

func TestHashA_FindElement(t *testing.T) {
	hash := NewHashATable()
	hash.AddElement("найдименя", "значение")

	t.Run("Поиск существующего элемента через FindElement", func(t *testing.T) {
		result := hash.FindElement("найдименя")
		if result != -1 {
			t.Errorf("FindElement должен возвращать -1 для строковых значений, получено %d", result)
		}
	})

	t.Run("Поиск существующего элемента через FindElementStr", func(t *testing.T) {
		result := hash.FindElementStr("найдименя")
		if result != "значение" {
			t.Errorf("Ожидалось 'значение', получено '%s'", result)
		}
	})

	t.Run("Поиск несуществующего элемента", func(t *testing.T) {
		result := hash.FindElementStr("несуществующий")
		if result != "-1" {
			t.Errorf("Ожидалось '-1' для несуществующего элемента, получено '%s'", result)
		}
	})

	t.Run("Поиск удаленного элемента", func(t *testing.T) {
		hash.AddElement("удаленный", "значение")
		hash.DeleteElement("удаленный")

		result := hash.FindElementStr("удаленный")
		if result != "-1" {
			t.Error("Удаленный элемент все еще находится")
		}
	})
}

func TestHashA_DeleteElement(t *testing.T) {
	hash := NewHashATable()
	hash.AddElement("удалименя", "значение")
	hash.AddElement("сосед", "другое_значение")

	t.Run("Удаление существующего элемента", func(t *testing.T) {
		initialSize := hash.size
		hash.DeleteElement("удалименя")

		if hash.size != initialSize-1 {
			t.Error("Размер не уменьшился после удаления")
		}

		result := hash.FindElementStr("удалименя")
		if result != "-1" {
			t.Error("Элемент не удален")
		}

		// Проверяем, что соседний элемент остался
		if hash.FindElementStr("сосед") != "другое_значение" {
			t.Error("Соседний элемент удален ошибочно")
		}
	})

	t.Run("Удаление несуществующего элемента", func(t *testing.T) {
		initialSize := hash.size
		hash.DeleteElement("несуществующий")
		if hash.size != initialSize {
			t.Error("Размер изменился при удалении несуществующего элемента")
		}
	})

	t.Run("Удаление из пустой таблицы", func(t *testing.T) {
		emptyHash := NewHashATable()
		emptyHash.DeleteElement("что-то")
	})
}

func TestHashA_PrintHashTable(t *testing.T) {
	t.Run("Печать пустой таблицы", func(t *testing.T) {
		hash := NewHashATable()
		hash.PrintHashTable()
	})

	t.Run("Печать непустой таблицы", func(t *testing.T) {
		hash := NewHashATable()
		hash.AddElement("печать1", "значение1")
		hash.AddElement("печать2", "значение2")
		hash.PrintHashTable()
	})

	t.Run("Печать таблицы с удаленными элементами", func(t *testing.T) {
		hash := NewHashATable()
		hash.AddElement("удаляемый", "значение")
		hash.DeleteElement("удаляемый")
		hash.PrintHashTable()
	})
}

func TestHashA_rehash(t *testing.T) {
	t.Run("Рехэширование при заполнении", func(t *testing.T) {
		hash := NewHashATable()
		initialCapacity := hash.capacity

		// Заполняем таблицу более чем на 75%
		for i := 0; i < 7; i++ {
			hash.AddElement("ключ"+strconv.Itoa(i), "значение"+strconv.Itoa(i))
		}

		if hash.capacity <= initialCapacity {
			t.Error("Рехэширование не увеличило емкость")
		}
		if hash.size != 7 {
			t.Errorf("Ожидался размер 7 после рехэширования, получено %d", hash.size)
		}

		// Проверяем, что все элементы доступны после рехэширования
		for i := 0; i < 7; i++ {
			result := hash.FindElementStr("ключ" + strconv.Itoa(i))
			if result != "значение"+strconv.Itoa(i) {
				t.Errorf("Элемент ключ%d потерян после рехэширования", i)
			}
		}
	})
}
