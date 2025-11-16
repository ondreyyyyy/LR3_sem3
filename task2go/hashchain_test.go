package main

import (
	"testing"
)

func TestNewHashTable(t *testing.T) {
	t.Run("Создание хэш-таблицы", func(t *testing.T) {
		hash := NewHashTable()
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
	})
}

func TestHashTable_hashFunc(t *testing.T) {
	hash := NewHashTable()

	t.Run("Хэш-функция для разных ключей", func(t *testing.T) {
		key1 := "test"
		key2 := "test2"

		hash1 := hash.hashFunc(key1)
		hash2 := hash.hashFunc(key2)

		if hash1 < 0 || hash1 >= hash.capacity {
			t.Error("Хэш выходит за границы таблицы")
		}
		if hash2 < 0 || hash2 >= hash.capacity {
			t.Error("Хэш выходит за границы таблицы")
		}
	})

	t.Run("Хэш-функция для одинаковых ключей", func(t *testing.T) {
		key := "одинаковый"
		hash1 := hash.hashFunc(key)
		hash2 := hash.hashFunc(key)

		if hash1 != hash2 {
			t.Error("Хэш-функция не детерминирована")
		}
	})
}

func TestHashTable_AddElement(t *testing.T) {
	hash := NewHashTable()

	t.Run("Добавление нового элемента", func(t *testing.T) {
		hash.AddElement("ключ1", 100)
		if hash.size != 1 {
			t.Errorf("Ожидался размер 1, получено %d", hash.size)
		}

		result := hash.FindElement("ключ1")
		if result != 100 {
			t.Errorf("Ожидалось 100, получено %d", result)
		}
	})

	t.Run("Обновление существующего элемента", func(t *testing.T) {
		hash.AddElement("ключ1", 200) // Обновление
		if hash.size != 1 {
			t.Error("Размер не должен меняться при обновлении")
		}

		result := hash.FindElement("ключ1")
		if result != 200 {
			t.Errorf("Ожидалось 200 после обновления, получено %d", result)
		}
	})

	t.Run("Добавление нескольких элементов", func(t *testing.T) {
		hash.AddElement("ключ2", 300)
		hash.AddElement("ключ3", 400)

		if hash.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", hash.size)
		}

		if hash.FindElement("ключ2") != 300 {
			t.Error("Второй элемент не найден")
		}
		if hash.FindElement("ключ3") != 400 {
			t.Error("Третий элемент не найден")
		}
	})

	t.Run("Коллизии хэшей", func(t *testing.T) {
		// Добавляем элементы, которые могут иметь одинаковый хэш
		hash.AddElement("a", 1)
		hash.AddElement("b", 2)
		hash.AddElement("c", 3)

		if hash.size != 6 { // 3 предыдущих + 3 новых
			t.Errorf("Ожидался размер 6, получено %d", hash.size)
		}
	})
}

func TestHashTable_FindElement(t *testing.T) {
	hash := NewHashTable()
	hash.AddElement("найдименя", 999)

	t.Run("Поиск существующего элемента", func(t *testing.T) {
		result := hash.FindElement("найдименя")
		if result != 999 {
			t.Errorf("Ожидалось 999, получено %d", result)
		}
	})

	t.Run("Поиск несуществующего элемента", func(t *testing.T) {
		result := hash.FindElement("несуществующий")
		if result != -1 {
			t.Errorf("Ожидалось -1 для несуществующего элемента, получено %d", result)
		}
	})

	t.Run("Поиск в пустой таблице", func(t *testing.T) {
		emptyHash := NewHashTable()
		result := emptyHash.FindElement("что-то")
		if result != -1 {
			t.Error("Поиск в пустой таблице должен возвращать -1")
		}
	})
}

func TestHashTable_DeleteElement(t *testing.T) {
	hash := NewHashTable()
	hash.AddElement("удалименя", 500)
	hash.AddElement("сосед", 600)

	t.Run("Удаление существующего элемента", func(t *testing.T) {
		initialSize := hash.size
		hash.DeleteElement("удалименя")

		if hash.size != initialSize-1 {
			t.Error("Размер не уменьшился после удаления")
		}

		result := hash.FindElement("удалименя")
		if result != -1 {
			t.Error("Элемент не удален")
		}

		// Проверяем, что соседний элемент остался
		if hash.FindElement("сосед") != 600 {
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
		emptyHash := NewHashTable()
		emptyHash.DeleteElement("что-то")
	})
}

func TestHashTable_PrintHashTable(t *testing.T) {
	t.Run("Печать пустой таблицы", func(t *testing.T) {
		hash := NewHashTable()
		hash.PrintHashTable()
	})

	t.Run("Печать непустой таблицы", func(t *testing.T) {
		hash := NewHashTable()
		hash.AddElement("печать1", 1)
		hash.AddElement("печать2", 2)
		hash.PrintHashTable()
	})
}
