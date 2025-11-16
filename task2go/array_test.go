package main

import (
	"strconv"
	"testing"
)

func TestNewDynArray(t *testing.T) {
	t.Run("Создание массива с положительной емкостью", func(t *testing.T) {
		arr := NewDynArray(5)
		if arr == nil {
			t.Error("Конструктор вернул nil")
		}
		if arr.capacity != 5 {
			t.Errorf("Ожидалась емкость 5, получено %d", arr.capacity)
		}
		if arr.size != 0 {
			t.Errorf("Ожидался размер 0, получено %d", arr.size)
		}
	})

	t.Run("Создание массива с нулевой емкостью", func(t *testing.T) {
		arr := NewDynArray(0)
		if arr.capacity != 1 {
			t.Errorf("Ожидалась емкость по умолчанию 1, получено %d", arr.capacity)
		}
	})

	t.Run("Создание массива с отрицательной емкостью", func(t *testing.T) {
		arr := NewDynArray(-5)
		if arr.capacity != 1 {
			t.Errorf("Ожидалась емкость по умолчанию 1, получено %d", arr.capacity)
		}
	})
}

func TestDynArray_Resize(t *testing.T) {
	t.Run("Увеличение вместимости массива вдвое", func(t *testing.T) {
		arr := NewDynArray(2) // Начальная емкость 2

		// Заполняем массив до предела
		arr.PushBack("элемент1")
		arr.PushBack("элемент2")

		initialCapacity := arr.Capacity()

		// Добавляем третий элемент - должен вызвать увеличение емкости
		arr.PushBack("элемент3")

		if arr.Capacity() != initialCapacity*2 {
			t.Errorf("Ожидалось увеличение емкости с %d до %d, получено %d",
				initialCapacity, initialCapacity*2, arr.Capacity())
		}
		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}

		// Проверяем, что все элементы сохранились
		val1, _ := arr.GetElement(0)
		val2, _ := arr.GetElement(1)
		val3, _ := arr.GetElement(2)

		if val1 != "элемент1" || val2 != "элемент2" || val3 != "элемент3" {
			t.Error("Элементы потеряны при увеличении емкости")
		}
	})

	t.Run("Многократное увеличение емкости", func(t *testing.T) {
		arr := NewDynArray(2)

		// Добавляем много элементов
		for i := 0; i < 10; i++ {
			arr.PushBack(strconv.Itoa(i))
		}

		if arr.size != 10 {
			t.Errorf("Ожидался размер 10, получено %d", arr.size)
		}
		if arr.Capacity() < 10 {
			t.Errorf("Емкость %d недостаточна для 10 элементов", arr.Capacity())
		}

		// Проверяем целостность данных
		for i := 0; i < 10; i++ {
			val, _ := arr.GetElement(i)
			if val != strconv.Itoa(i) {
				t.Errorf("Элемент %d поврежден: ожидалось %s, получено %s", i, strconv.Itoa(i), val)
			}
		}
	})

	t.Run("Resize при добавлении в середину", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("a")
		arr.PushBack("b") // Массив заполнен, следующее добавление вызовет resize

		// Добавляем в середину, что должно вызвать resize
		arr.AddAtIndex(1, "c")

		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}
		if arr.capacity != 4 {
			t.Errorf("Ожидалась емкость 4, получено %d", arr.capacity)
		}

		// Проверяем порядок элементов
		val0, _ := arr.GetElement(0)
		val1, _ := arr.GetElement(1)
		val2, _ := arr.GetElement(2)

		if val0 != "a" || val1 != "c" || val2 != "b" {
			t.Errorf("Неправильный порядок элементов: %s, %s, %s", val0, val1, val2)
		}
	})
}

func TestDynArray_AddAtIndex(t *testing.T) {
	t.Run("Добавление в начало пустого массива", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.AddAtIndex(0, "первый")
		if arr.size != 1 {
			t.Errorf("Ожидался размер 1, получено %d", arr.size)
		}
		val, err := arr.GetElement(0)
		if err != nil || val != "первый" {
			t.Error("Не удалось добавить элемент в начало")
		}
	})

	t.Run("Добавление в конец", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.AddAtIndex(0, "первый")
		arr.AddAtIndex(1, "третий")
		if arr.size != 2 {
			t.Errorf("Ожидался размер 2, получено %d", arr.size)
		}
	})

	t.Run("Добавление в середину", func(t *testing.T) {
		arr := NewDynArray(3)
		arr.AddAtIndex(0, "первый")
		arr.AddAtIndex(1, "третий")
		arr.AddAtIndex(1, "второй")
		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}
		val, _ := arr.GetElement(1)
		if val != "второй" {
			t.Error("Не удалось добавить элемент в середину")
		}
		// Проверяем порядок элементов
		val0, _ := arr.GetElement(0)
		val1, _ := arr.GetElement(1)
		val2, _ := arr.GetElement(2)
		if val0 != "первый" || val1 != "второй" || val2 != "третий" {
			t.Error("Неправильный порядок элементов после добавления в середину")
		}
	})

	t.Run("Добавление с отрицательным индексом", func(t *testing.T) {
		arr := NewDynArray(2)
		initialSize := arr.size
		arr.AddAtIndex(-1, "невалидный")
		if arr.size != initialSize {
			t.Error("Массив изменился при добавлении с отрицательным индексом")
		}
	})

	t.Run("Добавление с индексом больше размера", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("a")
		initialSize := arr.size
		arr.AddAtIndex(100, "невалидный")
		if arr.size != initialSize {
			t.Error("Массив изменился при добавлении с индексом больше размера")
		}
	})

	t.Run("Добавление с вызовом resize", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("a")
		arr.PushBack("b") // Массив заполнен

		// Добавляем еще один элемент - должен вызвать resize
		initialCapacity := arr.capacity
		arr.AddAtIndex(1, "c")

		if arr.capacity <= initialCapacity {
			t.Error("Resize не был вызван")
		}
		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}
	})

	t.Run("Добавление в самый конец с помощью AddAtIndex", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("a")
		arr.PushBack("b")
		arr.AddAtIndex(2, "c") // Добавление в конец

		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}
		val, _ := arr.GetElement(2)
		if val != "c" {
			t.Error("Не удалось добавить элемент в конец через AddAtIndex")
		}
	})
}

func TestDynArray_PushBack(t *testing.T) {
	t.Run("Добавление элементов", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("элемент1")
		arr.PushBack("элемент2")
		if arr.size != 2 {
			t.Errorf("Ожидался размер 2, получено %d", arr.size)
		}
	})

	t.Run("Автоматическое увеличение емкости", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("элемент1")
		arr.PushBack("элемент2")
		arr.PushBack("элемент3") // Должен вызвать resize
		if arr.capacity != 4 {
			t.Errorf("Ожидалась емкость 4 после увеличения, получено %d", arr.capacity)
		}
		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}
	})

	t.Run("Многократное добавление с resize", func(t *testing.T) {
		arr := NewDynArray(1)
		for i := 0; i < 100; i++ {
			arr.PushBack(strconv.Itoa(i))
		}
		if arr.size != 100 {
			t.Errorf("Ожидался размер 100, получено %d", arr.size)
		}
		// Проверяем последний элемент
		val, _ := arr.GetElement(99)
		if val != "99" {
			t.Errorf("Ожидался '99', получено '%s'", val)
		}
	})
}

func TestDynArray_GetElement(t *testing.T) {
	arr := NewDynArray(3)
	arr.PushBack("первый")
	arr.PushBack("второй")
	arr.PushBack("третий")

	t.Run("Корректное получение элементов", func(t *testing.T) {
		val, err := arr.GetElement(0)
		if err != nil || val != "первый" {
			t.Error("Не удалось получить первый элемент")
		}

		val, err = arr.GetElement(2)
		if err != nil || val != "третий" {
			t.Error("Не удалось получить третий элемент")
		}
	})

	t.Run("Получение с отрицательным индексом", func(t *testing.T) {
		_, err := arr.GetElement(-1)
		if err == nil {
			t.Error("Ожидалась ошибка для отрицательного индекса")
		}
	})

	t.Run("Получение с индексом больше размера", func(t *testing.T) {
		_, err := arr.GetElement(10)
		if err == nil {
			t.Error("Ожидалась ошибка для индекса больше размера")
		}
	})

	t.Run("Получение с индексом равным размеру", func(t *testing.T) {
		_, err := arr.GetElement(3)
		if err == nil {
			t.Error("Ожидалась ошибка для индекса равного размеру")
		}
	})
}

func TestDynArray_RemoveFromIndex(t *testing.T) {
	t.Run("Удаление из середины", func(t *testing.T) {
		arr := NewDynArray(3)
		arr.PushBack("первый")
		arr.PushBack("второй")
		arr.PushBack("третий")

		arr.RemoveFromIndex(1)
		if arr.size != 2 {
			t.Errorf("Ожидался размер 2 после удаления, получено %d", arr.size)
		}
		val, _ := arr.GetElement(1)
		if val != "третий" {
			t.Error("Элементы не сдвинулись корректно после удаления")
		}
	})

	t.Run("Удаление из начала", func(t *testing.T) {
		arr := NewDynArray(3)
		arr.PushBack("первый")
		arr.PushBack("второй")
		arr.PushBack("третий")

		arr.RemoveFromIndex(0)
		if arr.size != 2 {
			t.Errorf("Ожидался размер 2, получено %d", arr.size)
		}
		val, _ := arr.GetElement(0)
		if val != "второй" {
			t.Error("Первый элемент не удален корректно")
		}
	})

	t.Run("Удаление из конца", func(t *testing.T) {
		arr := NewDynArray(3)
		arr.PushBack("первый")
		arr.PushBack("второй")
		arr.PushBack("третий")

		arr.RemoveFromIndex(2)
		if arr.size != 2 {
			t.Errorf("Ожидался размер 2, получено %d", arr.size)
		}
		// Попытка получить удаленный элемент должна вызвать ошибку
		_, err := arr.GetElement(2)
		if err == nil {
			t.Error("Удаленный элемент все еще доступен")
		}
	})

	t.Run("Удаление с невалидным индексом", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("a")
		arr.PushBack("b")
		initialSize := arr.size
		arr.RemoveFromIndex(-1)
		arr.RemoveFromIndex(10)
		if arr.size != initialSize {
			t.Error("Размер изменился при удалении с невалидным индексом")
		}
	})

	t.Run("Удаление из пустого массива", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.RemoveFromIndex(0)
		if arr.size != 0 {
			t.Error("Размер пустого массива изменился после удаления")
		}
	})
}

func TestDynArray_ReplaceElement(t *testing.T) {
	t.Run("Корректная замена", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("старый")
		arr.PushBack("второй")

		arr.ReplaceElement(0, "новый")
		val, _ := arr.GetElement(0)
		if val != "новый" {
			t.Error("Элемент не был заменен")
		}
		// Проверяем, что второй элемент не изменился
		val, _ = arr.GetElement(1)
		if val != "второй" {
			t.Error("Второй элемент изменился при замене первого")
		}
	})

	t.Run("Замена с невалидным индексом", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("оригинал")

		arr.ReplaceElement(-1, "невалидный")
		arr.ReplaceElement(10, "невалидный")

		// Проверяем, что массив не изменился
		val, _ := arr.GetElement(0)
		if val != "оригинал" {
			t.Error("Элементы изменились при невалидной замене")
		}
	})

	t.Run("Замена последнего элемента", func(t *testing.T) {
		arr := NewDynArray(3)
		arr.PushBack("a")
		arr.PushBack("b")
		arr.PushBack("c")

		arr.ReplaceElement(2, "новый_хвост")
		val, _ := arr.GetElement(2)
		if val != "новый_хвост" {
			t.Error("Последний элемент не заменен")
		}
	})
}

func TestDynArray_LengthAndCapacity(t *testing.T) {
	t.Run("Проверка длины", func(t *testing.T) {
		arr := NewDynArray(5)
		arr.PushBack("элемент1")
		arr.PushBack("элемент2")

		if arr.Length() != 2 {
			t.Errorf("Ожидалась длина 2, получено %d", arr.Length())
		}
	})

	t.Run("Проверка емкости", func(t *testing.T) {
		arr := NewDynArray(5)
		if arr.Capacity() != 5 {
			t.Errorf("Ожидалась емкость 5, получено %d", arr.Capacity())
		}
	})

	t.Run("Изменение емкости при добавлении", func(t *testing.T) {
		arr := NewDynArray(2)
		initialCapacity := arr.Capacity()
		arr.PushBack("a")
		arr.PushBack("b")
		arr.PushBack("c") // Должен вызвать resize

		if arr.Capacity() == initialCapacity {
			t.Error("Емкость не изменилась после добавления элементов")
		}
	})
}

func TestDynArray_Print(t *testing.T) {
	t.Run("Печать пустого массива", func(t *testing.T) {
		arr := NewDynArray(2)
		// Этот тест в основном проверяет, что метод не паникует
		arr.Print()
	})

	t.Run("Печать непустого массива", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("тест1")
		arr.PushBack("тест2")
		// Этот тест в основном проверяет, что метод не паникает
		arr.Print()
	})
}

func TestDynArray_EdgeCases(t *testing.T) {
	t.Run("Последовательные операции добавления и удаления", func(t *testing.T) {
		arr := NewDynArray(2)

		// Добавляем элементы
		for i := 0; i < 5; i++ {
			arr.PushBack(strconv.Itoa(i))
		}

		// Удаляем некоторые элементы
		arr.RemoveFromIndex(2)
		arr.RemoveFromIndex(0)

		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}

		// Проверяем оставшиеся элементы
		val0, _ := arr.GetElement(0)
		val1, _ := arr.GetElement(1)
		val2, _ := arr.GetElement(2)

		if val0 != "1" || val1 != "3" || val2 != "4" {
			t.Errorf("Неправильный порядок после удалений: %s, %s, %s", val0, val1, val2)
		}

		// Добавляем еще элементы
		arr.AddAtIndex(1, "новый")
		arr.PushBack("последний")

		if arr.size != 5 {
			t.Errorf("Ожидался размер 5, получено %d", arr.size)
		}
	})

	t.Run("Работа с массивом емкостью 1", func(t *testing.T) {
		arr := NewDynArray(1)
		arr.PushBack("первый")
		arr.PushBack("второй") // Должен вызвать resize

		if arr.size != 2 {
			t.Errorf("Ожидался размер 2, получено %d", arr.size)
		}
		if arr.capacity < 2 {
			t.Errorf("Емкость должна быть не менее 2, получено %d", arr.capacity)
		}
	})

	t.Run("Многократные замены элементов", func(t *testing.T) {
		arr := NewDynArray(3)
		arr.PushBack("a")
		arr.PushBack("b")
		arr.PushBack("c")

		arr.ReplaceElement(0, "x")
		arr.ReplaceElement(1, "y")
		arr.ReplaceElement(2, "z")

		val0, _ := arr.GetElement(0)
		val1, _ := arr.GetElement(1)
		val2, _ := arr.GetElement(2)

		if val0 != "x" || val1 != "y" || val2 != "z" {
			t.Errorf("Замена не работает: %s, %s, %s", val0, val1, val2)
		}
	})

	t.Run("Ошибка outOfRangeError", func(t *testing.T) {
		arr := NewDynArray(2)
		_, err := arr.GetElement(5)

		if err == nil {
			t.Error("Ожидалась ошибка outOfRangeError")
		}

		if err.Error() != "Индекс не является элементом массива." {
			t.Errorf("Неправильное сообщение об ошибке: %s", err.Error())
		}
	})
}

func TestDynArray_ComplexScenarios(t *testing.T) {
	t.Run("Сложный сценарий с добавлением и удалением", func(t *testing.T) {
		arr := NewDynArray(2)

		// Этап 1: Заполнение массива
		arr.PushBack("a")
		arr.PushBack("b") // Емкость = 2, размер = 2

		// Этап 2: Добавление с вызовом resize
		arr.AddAtIndex(1, "c") // Должен вызвать resize до 4

		if arr.capacity != 4 {
			t.Errorf("Ожидалась емкость 4, получено %d", arr.capacity)
		}
		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}

		// Этап 3: Удаление элементов
		arr.RemoveFromIndex(0) // Удаляем "a"
		if arr.size != 2 {
			t.Errorf("Ожидался размер 2, получено %d", arr.size)
		}

		// Этап 4: Проверка конечного состояния
		val0, _ := arr.GetElement(0)
		val1, _ := arr.GetElement(1)

		if val0 != "c" || val1 != "b" {
			t.Errorf("Неправильный конечный порядок: %s, %s", val0, val1)
		}
	})

	t.Run("Добавление в начало с resize", func(t *testing.T) {
		arr := NewDynArray(2)
		arr.PushBack("b")
		arr.PushBack("c") // Массив заполнен

		// Добавляем в начало - должен вызвать resize
		arr.AddAtIndex(0, "a")

		if arr.size != 3 {
			t.Errorf("Ожидался размер 3, получено %d", arr.size)
		}
		if arr.capacity != 4 {
			t.Errorf("Ожидалась емкость 4, получено %d", arr.capacity)
		}

		// Проверяем порядок
		val0, _ := arr.GetElement(0)
		val1, _ := arr.GetElement(1)
		val2, _ := arr.GetElement(2)

		if val0 != "a" || val1 != "b" || val2 != "c" {
			t.Errorf("Неправильный порядок: %s, %s, %s", val0, val1, val2)
		}
	})
}
