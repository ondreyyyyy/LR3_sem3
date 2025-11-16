package main

import (
	"testing"
)

func TestNewForwardList(t *testing.T) {
	t.Run("Создание списка с одним элементом", func(t *testing.T) {
		list := NewForwardList("голова")
		if list.head == nil || list.tail == nil {
			t.Error("Голова или хвост не установлены")
		}
		if list.head.value != "голова" {
			t.Errorf("Ожидалось значение 'голова', получено '%s'", list.head.value)
		}
		if list.head != list.tail {
			t.Error("Голова и хвост должны быть одинаковыми для списка с одним элементом")
		}
	})
}

func TestForwardList_AddAtHead(t *testing.T) {
	t.Run("Добавление в голову непустого списка", func(t *testing.T) {
		list := NewForwardList("начальный")
		list.AddAtHead("новая_голова")
		if list.head.value != "новая_голова" {
			t.Errorf("Ожидалось 'новая_голова', получено '%s'", list.head.value)
		}
		if list.head.next.value != "начальный" {
			t.Error("Связь между элементами нарушена")
		}
	})

	t.Run("Добавление в голову пустого списка", func(t *testing.T) {
		emptyList := &ForwardList{}
		emptyList.AddAtHead("элемент")
		if emptyList.head == nil || emptyList.head.value != "элемент" {
			t.Error("Не удалось добавить элемент в пустой список")
		}
		if emptyList.tail != emptyList.head {
			t.Error("Хвост не установлен корректно для пустого списка")
		}
	})
}

func TestForwardList_AddAtTail(t *testing.T) {
	t.Run("Добавление в хвост", func(t *testing.T) {
		list := NewForwardList("первый")
		list.AddAtTail("второй")
		if list.tail.value != "второй" {
			t.Errorf("Ожидалось 'второй', получено '%s'", list.tail.value)
		}
		if list.head.next != list.tail {
			t.Error("Связь между головой и хвостом нарушена")
		}
	})

	t.Run("Добавление в хвост пустого списка", func(t *testing.T) {
		emptyList := &ForwardList{}
		emptyList.AddAtTail("элемент")
		if emptyList.head == nil || emptyList.head.value != "элемент" {
			t.Error("Не удалось добавить элемент в хвост пустого списка")
		}
	})
}

func TestForwardList_SearchNode(t *testing.T) {
	list := NewForwardList("первый")
	list.AddAtTail("второй")
	list.AddAtTail("третий")

	t.Run("Поиск существующего элемента", func(t *testing.T) {
		list.SearchNode("второй")
	})

	t.Run("Поиск несуществующего элемента", func(t *testing.T) {
		list.SearchNode("несуществующий")
	})

	t.Run("Поиск в пустом списке", func(t *testing.T) {
		emptyList := &ForwardList{}
		emptyList.SearchNode("что-то")
	})
}

func TestForwardList_AddBeforeIndex(t *testing.T) {
	list := NewForwardList("ноль")
	list.AddAtTail("один")
	list.AddAtTail("два")

	t.Run("Добавление перед индексом 0", func(t *testing.T) {
		list.AddBeforeIndex("перед_нулем", 0)
		if list.head.value != "перед_нулем" {
			t.Error("Элемент не добавлен перед индексом 0")
		}
	})

	t.Run("Добавление перед средним индексом", func(t *testing.T) {
		initialSize := getForwardListSize(list)
		list.AddBeforeIndex("перед_двумя", 3)
		if getForwardListSize(list) != initialSize+1 {
			t.Error("Элемент не добавлен перед указанным индексом")
		}
	})

	t.Run("Добавление с отрицательным индексом", func(t *testing.T) {
		initialSize := getForwardListSize(list)
		list.AddBeforeIndex("невалидный", -1)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при добавлении с отрицательным индексом")
		}
	})

	t.Run("Добавление с индексом больше размера", func(t *testing.T) {
		initialSize := getForwardListSize(list)
		list.AddBeforeIndex("невалидный", 100)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при добавлении с индексом больше размера")
		}
	})

}

func TestForwardList_AddAfterIndex(t *testing.T) {
	list := NewForwardList("ноль")
	list.AddAtTail("один")

	t.Run("Добавление после индекса", func(t *testing.T) {
		list.AddAfterIndex("после_нуля", 0)
		if list.head.next.value != "после_нуля" {
			t.Error("Элемент не добавлен после указанного индекса")
		}
	})

	t.Run("Добавление после хвоста", func(t *testing.T) {
		list.AddAfterIndex("новый_хвост", 2)
		if list.tail.value != "новый_хвост" {
			t.Error("Хвост не обновлен при добавлении после последнего элемента")
		}
	})

	t.Run("Добавление с невалидным индексом", func(t *testing.T) {
		initialSize := getForwardListSize(list)
		list.AddAfterIndex("невалидный", -1)
		list.AddAfterIndex("невалидный", 100)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при невалидном добавлении")
		}
	})
}

func TestForwardList_DeleteOperations(t *testing.T) {
	t.Run("Удаление головы", func(t *testing.T) {
		list := NewForwardList("голова")
		list.AddAtTail("хвост")
		list.DeleteAtHead()
		if list.head.value != "хвост" {
			t.Error("Голова не удалена корректно")
		}
	})

	t.Run("Удаление хвоста", func(t *testing.T) {
		list := NewForwardList("голова")
		list.AddAtTail("хвост")
		list.DeleteAtTail()
		if list.tail != list.head {
			t.Error("Хвост не удален корректно")
		}
		if list.head.value != "голова" {
			t.Error("Голова изменилась при удалении хвоста")
		}
	})

	t.Run("Удаление по значению", func(t *testing.T) {
		list := NewForwardList("первый")
		list.AddAtTail("второй")
		list.AddAtTail("третий")

		list.DeleteValue("второй")
		if list.head.next.value != "третий" {
			t.Error("Элемент не удален по значению")
		}
	})

	t.Run("Удаление перед индексом", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		list.AddAtTail("2")
		list.AddAtTail("3")

		initialSize := getForwardListSize(list)
		list.DeleteBeforeIndex(2)
		if getForwardListSize(list) != initialSize-1 {
			t.Error("Элемент не удален перед указанным индексом")
		}
	})

	t.Run("Удаление после индекса", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		list.AddAtTail("2")
		list.AddAtTail("3")

		initialSize := getForwardListSize(list)
		list.DeleteAfterIndex(1)
		if getForwardListSize(list) != initialSize-1 {
			t.Error("Элемент не удален после указанного индекса")
		}
	})

	t.Run("Удаление из пустого списка", func(t *testing.T) {
		emptyList := &ForwardList{}

		emptyList.DeleteAtHead()
		emptyList.DeleteAtTail()
		emptyList.DeleteValue("что-то")
		emptyList.DeleteBeforeIndex(0)
		emptyList.DeleteAfterIndex(0)
	})
}

func TestForwardList_Print(t *testing.T) {
	list := NewForwardList("тест1")
	list.AddAtTail("тест2")
	list.Print()
}

func TestForwardList_Getters(t *testing.T) {
	list := NewForwardList("голова")

	t.Run("Получение головы", func(t *testing.T) {
		if list.GetHead() != list.head {
			t.Error("GetHead возвращает неверное значение")
		}
	})

	t.Run("Получение хвоста", func(t *testing.T) {
		if list.GetTail() != list.tail {
			t.Error("GetTail возвращает неверное значение")
		}
	})

	t.Run("Проверка пустоты", func(t *testing.T) {
		if list.IsEmpty() {
			t.Error("Список не должен быть пустым")
		}
		emptyList := &ForwardList{}
		if !emptyList.IsEmpty() {
			t.Error("Пустой список должен возвращать true для IsEmpty")
		}
	})
}

func TestForwardList_DeleteBeforeIndex_EdgeCases(t *testing.T) {
	t.Run("Удаление перед индексом 0", func(t *testing.T) {
		list := NewForwardList("0")
		initialSize := getForwardListSize(list)
		list.DeleteBeforeIndex(0)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении перед индексом 0")
		}
	})

	t.Run("Удаление перед индексом 1", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		initialSize := getForwardListSize(list)
		list.DeleteBeforeIndex(1)
		if getForwardListSize(list) != initialSize-1 {
			t.Error("Элемент не удален перед индексом 1")
		}
		if list.head.value != "1" {
			t.Error("Голова не обновлена корректно после удаления перед индексом 1")
		}
	})

	t.Run("Удаление перед индексом в списке с одним элементом", func(t *testing.T) {
		list := NewForwardList("единственный")
		initialSize := getForwardListSize(list)
		list.DeleteBeforeIndex(1)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении перед индексом в списке с одним элементом")
		}
	})

	t.Run("Удаление перед индексом с отрицательным индексом", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		initialSize := getForwardListSize(list)
		list.DeleteBeforeIndex(-1)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении с отрицательным индексом")
		}
	})

	t.Run("Удаление перед индексом с индексом больше размера", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		initialSize := getForwardListSize(list)
		list.DeleteBeforeIndex(5)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении с индексом больше размера")
		}
	})

	t.Run("Удаление перед индексом в пустом списке", func(t *testing.T) {
		emptyList := &ForwardList{}
		emptyList.DeleteBeforeIndex(1)
		if !emptyList.IsEmpty() {
			t.Error("Пустой список должен оставаться пустым после операции удаления")
		}
	})
}

func TestForwardList_DeleteAfterIndex_EdgeCases(t *testing.T) {
	t.Run("Удаление после индекса в списке с несколькими элементами", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		list.AddAtTail("2")
		initialSize := getForwardListSize(list)
		list.DeleteAfterIndex(0)
		if getForwardListSize(list) != initialSize-1 {
			t.Error("Элемент не удален после указанного индекса")
		}
		if list.head.next.value != "2" {
			t.Error("Связи не обновлены корректно после удаления")
		}
	})

	t.Run("Удаление после последнего элемента", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		initialSize := getForwardListSize(list)
		list.DeleteAfterIndex(1)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении после последнего элемента")
		}
	})

	t.Run("Удаление после индекса с отрицательным индексом", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		initialSize := getForwardListSize(list)
		list.DeleteAfterIndex(-1)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении с отрицательным индексом")
		}
	})

	t.Run("Удаление после индекса с индексом больше размера", func(t *testing.T) {
		list := NewForwardList("0")
		list.AddAtTail("1")
		initialSize := getForwardListSize(list)
		list.DeleteAfterIndex(5)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении с индексом больше размера")
		}
	})

	t.Run("Удаление после индекса в пустом списке", func(t *testing.T) {
		emptyList := &ForwardList{}
		emptyList.DeleteAfterIndex(0)
		if !emptyList.IsEmpty() {
			t.Error("Пустой список должен оставаться пустым после операции удаления")
		}
	})

	t.Run("Удаление после индекса в списке с одним элементом", func(t *testing.T) {
		list := NewForwardList("единственный")
		initialSize := getForwardListSize(list)
		list.DeleteAfterIndex(0)
		if getForwardListSize(list) != initialSize {
			t.Error("Размер списка изменился при удалении после индекса в списке с одним элементом")
		}
	})
}

func getForwardListSize(list *ForwardList) int {
	count := 0
	current := list.head
	for current != nil {
		count++
		current = current.next
	}
	return count
}

func TestForwardList_EdgeCases(t *testing.T) {
	t.Run("Удаление несуществующего значения", func(t *testing.T) {
		list := NewForwardList("существующий")
		list.DeleteValue("несуществующий")
		if list.head.value != "существующий" {
			t.Error("Список изменился при удалении несуществующего значения")
		}
	})

	t.Run("Работа со списком из одного элемента", func(t *testing.T) {
		list := NewForwardList("единственный")

		// Добавление в голову
		list.AddAtHead("новая_голова")
		if list.head.value != "новая_голова" {
			t.Error("Некорректное добавление в голову списка с одним элементом")
		}
		if list.tail.value != "единственный" {
			t.Error("Хвост не обновлен при добавлении в голову")
		}

		// Восстанавливаем список из одного элемента для следующих тестов
		list = NewForwardList("единственный")

		// Добавление в хвост
		list.AddAtTail("новый_хвост")
		if list.tail.value != "новый_хвост" {
			t.Error("Некорректное добавление в хвост")
		}

		// Восстанавливаем список из одного элемента
		list = NewForwardList("единственный")

		// Удаление головы
		list.DeleteAtHead()
		if list.head != nil || list.tail != nil {
			t.Error("Список должен быть пустым после удаления единственного элемента")
		}

		// Создаем новый список для теста удаления хвоста
		list = NewForwardList("единственный")

		// Удаление хвоста
		list.DeleteAtTail()
		if list.head != nil || list.tail != nil {
			t.Error("Список должен быть пустым после удаления хвоста единственного элемента")
		}
	})

	t.Run("Операции с полностью пустым списком", func(t *testing.T) {
		list := &ForwardList{} // Полностью пустой список

		// Эти операции не должны паниковать
		list.DeleteAtHead()
		list.DeleteAtTail()
		list.DeleteValue("anything")
		list.DeleteBeforeIndex(0)
		list.DeleteAfterIndex(0)
		list.SearchNode("something")

		if !list.IsEmpty() {
			t.Error("Пустой список должен оставаться пустым после операций")
		}
	})
}
