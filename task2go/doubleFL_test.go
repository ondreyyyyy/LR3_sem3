package main

import (
	"testing"
)

func TestNewDoubleFL(t *testing.T) {
	t.Run("Создание двусвязного списка", func(t *testing.T) {
		list := NewDoubleFL("первый")
		if list.head == nil || list.tail == nil {
			t.Error("Голова или хвост не установлены")
		}
		if list.head.value != "первый" {
			t.Errorf("Ожидалось 'первый', получено '%s'", list.head.value)
		}
		if list.head != list.tail {
			t.Error("Голова и хвост должны быть одинаковыми для списка с одним элементом")
		}
		if list.head.next != nil || list.head.prev != nil {
			t.Error("У единственного элемента не должно быть связей")
		}
	})
}

func TestDoubleFL_AddAtHead(t *testing.T) {
	t.Run("Добавление в голову непустого списка", func(t *testing.T) {
		list := NewDoubleFL("исходный")
		list.AddAtHead("новая_голова")

		if list.head.value != "новая_голова" {
			t.Error("Новый элемент не стал головой")
		}
		if list.head.next.value != "исходный" {
			t.Error("Связь вперед не установлена")
		}
		if list.head.next.prev != list.head {
			t.Error("Обратная связь не установлена")
		}
	})

	t.Run("Добавление в голову пустого списка", func(t *testing.T) {
		list := &DoubleFL{}
		list.AddAtHead("элемент")

		if list.head == nil || list.head.value != "элемент" {
			t.Error("Элемент не добавлен в пустой список")
		}
		if list.tail != list.head {
			t.Error("Хвост не равен голове для списка с одним элементом")
		}
	})
}

func TestDoubleFL_AddAtTail(t *testing.T) {
	t.Run("Добавление в хвост непустого списка", func(t *testing.T) {
		list := NewDoubleFL("голова")
		list.AddAtTail("хвост")

		if list.tail.value != "хвост" {
			t.Error("Элемент не добавлен в хвост")
		}
		if list.head.next != list.tail {
			t.Error("Прямая связь не установлена")
		}
		if list.tail.prev != list.head {
			t.Error("Обратная связь не установлена")
		}
	})

	t.Run("Добавление в хвост пустого списка", func(t *testing.T) {
		list := &DoubleFL{}
		list.AddAtTail("элемент")

		if list.head == nil || list.head.value != "элемент" {
			t.Error("Элемент не добавлен в пустой список")
		}
		if list.tail != list.head {
			t.Error("Хвост не равен голове для списка с одним элементом")
		}
	})
}

func TestDoubleFL_AddBeforeIndex(t *testing.T) {
	t.Run("Добавление перед индексом 0", func(t *testing.T) {
		list := NewDoubleFL("ноль")
		list.AddAtTail("один")
		list.AddBeforeIndex("перед_нулем", 0)

		if list.head.value != "перед_нулем" {
			t.Error("Элемент не добавлен перед индексом 0")
		}
		if list.head.next.value != "ноль" {
			t.Error("Связи нарушены при добавлении перед индексом 0")
		}
	})

	t.Run("Добавление перед средним индексом", func(t *testing.T) {
		list := NewDoubleFL("ноль")
		list.AddAtTail("один")
		list.AddAtTail("два")

		initialSize := getDoubleListSize(list)
		list.AddBeforeIndex("перед_двумя", 2)

		if getDoubleListSize(list) != initialSize+1 {
			t.Error("Элемент не добавлен перед указанным индексом")
		}
	})

	t.Run("Добавление в пустой список", func(t *testing.T) {
		list := &DoubleFL{}
		list.AddBeforeIndex("элемент", 0)

		if list.head != nil {
			t.Error("Элемент не должен быть добавлен в пустой список")
		}
	})

	t.Run("Добавление с отрицательным индексом", func(t *testing.T) {
		list := NewDoubleFL("ноль")
		initialSize := getDoubleListSize(list)
		list.AddBeforeIndex("невалидный", -1)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при добавлении с отрицательным индексом")
		}
	})

	t.Run("Добавление с индексом больше размера", func(t *testing.T) {
		list := NewDoubleFL("ноль")
		initialSize := getDoubleListSize(list)
		list.AddBeforeIndex("невалидный", 100)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при добавлении с индексом больше размера")
		}
	})
}

func TestDoubleFL_AddAfterIndex(t *testing.T) {
	t.Run("Добавление после индекса", func(t *testing.T) {
		list := NewDoubleFL("ноль")
		list.AddAtTail("один")
		list.AddAfterIndex("после_нуля", 0)

		if list.head.next.value != "после_нуля" {
			t.Error("Элемент не добавлен после указанного индекса")
		}
		if list.head.next.prev != list.head {
			t.Error("Обратная связь не установлена")
		}
	})

	t.Run("Добавление после хвоста", func(t *testing.T) {
		list := NewDoubleFL("ноль")
		list.AddAtTail("один")
		list.AddAfterIndex("новый_хвост", 1)

		if list.tail.value != "новый_хвост" {
			t.Error("Хвост не обновлен при добавлении после последнего элемента")
		}
	})

	t.Run("Добавление в пустой список", func(t *testing.T) {
		list := &DoubleFL{}
		list.AddAfterIndex("элемент", 0)

		if list.head != nil {
			t.Error("Элемент не должен быть добавлен в пустой список")
		}
	})

	t.Run("Добавление с отрицательным индексом", func(t *testing.T) {
		list := NewDoubleFL("ноль")
		initialSize := getDoubleListSize(list)
		list.AddAfterIndex("невалидный", -1)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при добавлении с отрицательным индексом")
		}
	})

	t.Run("Добавление с индексом больше размера", func(t *testing.T) {
		list := NewDoubleFL("ноль")
		initialSize := getDoubleListSize(list)
		list.AddAfterIndex("невалидный", 100)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при добавлении с индексом больше размера")
		}
	})
}

func TestDoubleFL_DeleteAtHead(t *testing.T) {
	t.Run("Удаление головы из списка с несколькими элементами", func(t *testing.T) {
		list := NewDoubleFL("голова")
		list.AddAtTail("середина")
		list.AddAtTail("хвост")

		list.DeleteAtHead()
		if list.head.value != "середина" {
			t.Error("Голова не удалена корректно")
		}
		if list.head.prev != nil {
			t.Error("У новой головы не должно быть предыдущего элемента")
		}
	})

	t.Run("Удаление головы из списка с одним элементом", func(t *testing.T) {
		list := NewDoubleFL("единственный")
		list.DeleteAtHead()

		if list.head != nil || list.tail != nil {
			t.Error("Список должен быть пустым после удаления единственного элемента")
		}
	})

	t.Run("Удаление головы из пустого списка", func(t *testing.T) {
		list := &DoubleFL{}
		list.DeleteAtHead()

		if list.head != nil || list.tail != nil {
			t.Error("Пустой список должен оставаться пустым")
		}
	})
}

func TestDoubleFL_DeleteAtTail(t *testing.T) {
	t.Run("Удаление хвоста из списка с несколькими элементами", func(t *testing.T) {
		list := NewDoubleFL("голова")
		list.AddAtTail("середина")
		list.AddAtTail("хвост")

		list.DeleteAtTail()
		if list.tail.value != "середина" {
			t.Error("Хвост не удален корректно")
		}
		if list.tail.next != nil {
			t.Error("У нового хвоста не должно быть следующего элемента")
		}
	})

	t.Run("Удаление хвоста из списка с одним элементом", func(t *testing.T) {
		list := NewDoubleFL("единственный")
		list.DeleteAtTail()

		if list.head != nil || list.tail != nil {
			t.Error("Список должен быть пустым после удаления единственного элемента")
		}
	})

	t.Run("Удаление хвоста из пустого списка", func(t *testing.T) {
		list := &DoubleFL{}
		list.DeleteAtTail()

		if list.head != nil || list.tail != nil {
			t.Error("Пустой список должен оставаться пустым")
		}
	})
}

func TestDoubleFL_DeleteValue(t *testing.T) {
	t.Run("Удаление по значению из середины", func(t *testing.T) {
		list := NewDoubleFL("первый")
		list.AddAtTail("второй")
		list.AddAtTail("третий")

		list.DeleteValue("второй")
		if list.head.next.value != "третий" {
			t.Error("Элемент не удален по значению")
		}
		if list.head.next.prev != list.head {
			t.Error("Связи не обновлены после удаления")
		}
	})

	t.Run("Удаление головы по значению", func(t *testing.T) {
		list := NewDoubleFL("голова")
		list.AddAtTail("хвост")
		list.DeleteValue("голова")

		if list.head.value != "хвост" {
			t.Error("Голова не удалена по значению")
		}
	})

	t.Run("Удаление хвоста по значению", func(t *testing.T) {
		list := NewDoubleFL("голова")
		list.AddAtTail("хвост")
		list.DeleteValue("хвост")

		if list.tail.value != "голова" {
			t.Error("Хвост не удален по значению")
		}
	})

	t.Run("Удаление несуществующего значения", func(t *testing.T) {
		list := NewDoubleFL("элемент")
		initialSize := getDoubleListSize(list)
		list.DeleteValue("несуществующий")

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении несуществующего значения")
		}
	})

	t.Run("Удаление из пустого списка", func(t *testing.T) {
		list := &DoubleFL{}
		list.DeleteValue("что-то")

		if list.head != nil || list.tail != nil {
			t.Error("Пустой список должен оставаться пустым")
		}
	})
}

func TestDoubleFL_DeleteBeforeIndex(t *testing.T) {
	t.Run("Удаление перед индексом 1", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		list.AddAtTail("2")

		initialSize := getDoubleListSize(list)
		list.DeleteBeforeIndex(1)

		if getDoubleListSize(list) != initialSize-1 {
			t.Error("Элемент не удален перед индексом 1")
		}
		if list.head.value != "1" {
			t.Error("Голова не обновлена корректно")
		}
	})

	t.Run("Удаление перед индексом в середине", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		list.AddAtTail("2")
		list.AddAtTail("3")

		initialSize := getDoubleListSize(list)
		list.DeleteBeforeIndex(2)

		if getDoubleListSize(list) != initialSize-1 {
			t.Error("Элемент не удален перед указанным индексом")
		}
	})

	t.Run("Удаление перед индексом 0", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		initialSize := getDoubleListSize(list)
		list.DeleteBeforeIndex(0)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении перед индексом 0")
		}
	})

	t.Run("Удаление перед индексом с отрицательным индексом", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		initialSize := getDoubleListSize(list)
		list.DeleteBeforeIndex(-1)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении с отрицательным индексом")
		}
	})

	t.Run("Удаление перед индексом в списке с одним элементом", func(t *testing.T) {
		list := NewDoubleFL("единственный")
		initialSize := getDoubleListSize(list)
		list.DeleteBeforeIndex(1)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении в списке с одним элементом")
		}
	})

	t.Run("Удаление перед индексом с индексом больше размера", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		initialSize := getDoubleListSize(list)
		list.DeleteBeforeIndex(5)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении с индексом больше размера")
		}
	})

	t.Run("Удаление перед индексом в пустом списке", func(t *testing.T) {
		list := &DoubleFL{}
		list.DeleteBeforeIndex(1)

		if !list.IsEmpty() {
			t.Error("Пустой список должен оставаться пустым")
		}
	})

	t.Run("Удаление перед хвостом", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		list.AddAtTail("2")

		initialSize := getDoubleListSize(list)
		list.DeleteBeforeIndex(2)

		if getDoubleListSize(list) != initialSize-1 {
			t.Error("Элемент перед хвостом не удален")
		}
		if list.head.next.value != "2" {
			t.Error("Связи не обновлены корректно")
		}
	})
}

func TestDoubleFL_DeleteAfterIndex(t *testing.T) {
	t.Run("Удаление после индекса в середине", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		list.AddAtTail("2")
		list.AddAtTail("3")

		initialSize := getDoubleListSize(list)
		list.DeleteAfterIndex(1) // Должен удалить "2"

		if getDoubleListSize(list) != initialSize-1 {
			t.Error("Элемент не удален после указанного индекса")
		}
		// Проверяем, что после элемента "1" теперь идет "3"
		if list.head.next.value != "1" {
			t.Error("Первый элемент не корректен")
		}
		if list.head.next.next.value != "3" {
			t.Error("Элемент после удаления не корректен")
		}
		if list.head.next.next.prev.value != "1" {
			t.Error("Обратная связь не обновлена корректно")
		}
	})

	t.Run("Удаление после головы", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		list.AddAtTail("2")

		initialSize := getDoubleListSize(list)
		list.DeleteAfterIndex(0) // Должен удалить "1"

		if getDoubleListSize(list) != initialSize-1 {
			t.Error("Элемент после головы не удален")
		}
		if list.head.next.value != "2" {
			t.Error("После головы должен остаться элемент '2'")
		}
		if list.head.next.prev != list.head {
			t.Error("Обратная связь не установлена на голову")
		}
	})

	t.Run("Удаление после предпоследнего элемента", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		list.AddAtTail("2")

		initialSize := getDoubleListSize(list)
		list.DeleteAfterIndex(1) // Должен удалить "2" (хвост)

		if getDoubleListSize(list) != initialSize-1 {
			t.Error("Элемент после предпоследнего не удален")
		}
		if list.tail.value != "1" {
			t.Error("Хвост не обновлен корректно")
		}
		if list.tail.next != nil {
			t.Error("У хвоста не должно быть следующего элемента")
		}
	})

	t.Run("Удаление после хвоста", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		initialSize := getDoubleListSize(list)
		list.DeleteAfterIndex(1) // Попытка удалить после хвоста

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении после хвоста")
		}
	})

	t.Run("Удаление после индекса с отрицательным индексом", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		initialSize := getDoubleListSize(list)
		list.DeleteAfterIndex(-1)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении с отрицательным индексом")
		}
	})

	t.Run("Удаление после индекса в списке с одним элементом", func(t *testing.T) {
		list := NewDoubleFL("единственный")
		initialSize := getDoubleListSize(list)
		list.DeleteAfterIndex(0)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении в списке с одним элементом")
		}
	})

	t.Run("Удаление после индекса с индексом больше размера", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		initialSize := getDoubleListSize(list)
		list.DeleteAfterIndex(5)

		if getDoubleListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении с индексом больше размера")
		}
	})

	t.Run("Удаление после индекса в пустом списке", func(t *testing.T) {
		list := &DoubleFL{}
		list.DeleteAfterIndex(0)

		if !list.IsEmpty() {
			t.Error("Пустой список должен оставаться пустым")
		}
	})

	t.Run("Удаление когда следующий элемент - хвост", func(t *testing.T) {
		list := NewDoubleFL("0")
		list.AddAtTail("1")
		list.AddAtTail("2")

		initialSize := getDoubleListSize(list)
		list.DeleteAfterIndex(1) // Удаляем хвост "2"

		if getDoubleListSize(list) != initialSize-1 {
			t.Error("Хвост не удален через DeleteAfterIndex")
		}
		if list.tail.value != "1" {
			t.Error("Хвост не обновлен корректно")
		}
		if list.tail.next != nil {
			t.Error("У нового хвоста не должно быть следующего элемента")
		}
	})
}

func TestDoubleFL_SearchValue(t *testing.T) {
	t.Run("Поиск существующего элемента", func(t *testing.T) {
		list := NewDoubleFL("первый")
		list.AddAtTail("второй")
		list.AddAtTail("третий")

		// Здесь мы просто проверяем, что метод не паникует
		// В реальном тесте можно было бы перехватывать вывод
		list.SearchValue("второй")
	})

	t.Run("Поиск несуществующего элемента", func(t *testing.T) {
		list := NewDoubleFL("первый")
		list.AddAtTail("второй")

		list.SearchValue("несуществующий")
	})

	t.Run("Поиск в пустом списке", func(t *testing.T) {
		emptyList := &DoubleFL{}
		emptyList.SearchValue("что-то")
	})

	t.Run("Поиск головы", func(t *testing.T) {
		list := NewDoubleFL("голова")
		list.AddAtTail("хвост")

		list.SearchValue("голова")
	})

	t.Run("Поиск хвоста", func(t *testing.T) {
		list := NewDoubleFL("голова")
		list.AddAtTail("хвост")

		list.SearchValue("хвост")
	})
}

func TestDoubleFL_Getters(t *testing.T) {
	t.Run("Получение головы", func(t *testing.T) {
		list := NewDoubleFL("голова")
		if list.GetHead() != list.head {
			t.Error("GetHead возвращает неверное значение")
		}
	})

	t.Run("Получение хвоста", func(t *testing.T) {
		list := NewDoubleFL("голова")
		if list.GetTail() != list.tail {
			t.Error("GetTail возвращает неверное значение")
		}
	})

	t.Run("Проверка пустоты непустого списка", func(t *testing.T) {
		list := NewDoubleFL("голова")
		if list.IsEmpty() {
			t.Error("Список не должен быть пустым")
		}
	})

	t.Run("Проверка пустоты пустого списка", func(t *testing.T) {
		emptyList := &DoubleFL{}
		if !emptyList.IsEmpty() {
			t.Error("Пустой список должен возвращать true для IsEmpty")
		}
	})
}

func TestDoubleFL_Print(t *testing.T) {
	t.Run("Печать непустого списка", func(t *testing.T) {
		list := NewDoubleFL("тест1")
		list.AddAtTail("тест2")
		// Просто проверяем, что метод не паникует
		list.Print()
	})

	t.Run("Печать пустого списка", func(t *testing.T) {
		list := &DoubleFL{}
		list.Print()
	})
}

func TestDoubleFL_EdgeCases(t *testing.T) {
	t.Run("Все операции с пустым списком", func(t *testing.T) {
		list := &DoubleFL{}

		// Эти операции не должны паниковать
		list.AddAtHead("элемент") // Добавим элемент
		list.DeleteAtHead()       // Удалим его

		// Теперь список пустой, проверяем остальные операции
		list.DeleteAtHead()
		list.DeleteAtTail()
		list.DeleteValue("что-то")
		list.DeleteBeforeIndex(0)
		list.DeleteAfterIndex(0)
		list.SearchValue("что-то")
		list.Print()

		if !list.IsEmpty() {
			t.Error("Список должен оставаться пустым")
		}
	})

	t.Run("Операции со списком из одного элемента", func(t *testing.T) {
		list := NewDoubleFL("единственный")

		// Проверяем различные удаления
		list.DeleteBeforeIndex(1) // Не должно удалить
		list.DeleteAfterIndex(0)  // Не должно удалить

		if list.head == nil || list.tail == nil {
			t.Error("Список не должен быть пустым после некритичных операций")
		}

		// Удаляем по значению
		list.DeleteValue("единственный")
		if !list.IsEmpty() {
			t.Error("Список должен быть пустым после удаления единственного элемента")
		}
	})

	t.Run("Последовательные добавления и удаления", func(t *testing.T) {
		list := &DoubleFL{}

		// Добавляем несколько элементов
		list.AddAtHead("1")
		list.AddAtTail("2")
		list.AddAtHead("0")
		list.AddAtTail("3")

		if getDoubleListSize(list) != 4 {
			t.Error("Не все элементы добавлены")
		}

		// Удаляем в разном порядке
		list.DeleteAtHead()   // Удаляем "0"
		list.DeleteAtTail()   // Удаляем "3"
		list.DeleteValue("2") // Удаляем "2"

		if list.head.value != "1" || list.tail.value != "1" {
			t.Error("Некорректное состояние после удалений")
		}

		// Удаляем последний элемент
		list.DeleteAtHead()
		if !list.IsEmpty() {
			t.Error("Список должен быть пустым")
		}
	})
}

func getDoubleListSize(list *DoubleFL) int {
	count := 0
	current := list.head
	for current != nil {
		count++
		current = current.next
	}
	return count
}
