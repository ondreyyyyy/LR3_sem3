package main

import (
	"testing"
)

func TestNewQueue(t *testing.T) {
	t.Run("Создание новой очереди", func(t *testing.T) {
		queue := NewQueue()
		if queue == nil {
			t.Error("Конструктор вернул nil")
		}
		if queue.head != nil || queue.tail != nil {
			t.Error("Голова и хвост должны быть nil при создании")
		}
	})
}

func TestQueue_Enqueue(t *testing.T) {
	queue := NewQueue()

	t.Run("Добавление первого элемента", func(t *testing.T) {
		queue.Enqueue("первый")
		if queue.head == nil || queue.tail == nil {
			t.Error("Голова или хвост не установлены")
		}
		if queue.head != queue.tail {
			t.Error("Голова и хвост должны быть одинаковыми для одного элемента")
		}
		if queue.head.value != "первый" {
			t.Errorf("Ожидалось 'первый', получено '%s'", queue.head.value)
		}
	})

	t.Run("Добавление нескольких элементов", func(t *testing.T) {
		queue.Enqueue("второй")
		queue.Enqueue("третий")

		if queue.head.value != "первый" {
			t.Error("Голова не должна меняться при добавлении в очередь")
		}
		if queue.tail.value != "третий" {
			t.Error("Хвост должен обновляться при добавлении")
		}
		if queue.head.next.value != "второй" {
			t.Error("Связи между элементами нарушены")
		}
		if queue.head.next.next != queue.tail {
			t.Error("Последний элемент не связан с хвостом")
		}
	})
}

func TestQueue_Dequeue(t *testing.T) {
	t.Run("Удаление из пустой очереди", func(t *testing.T) {
		queue := NewQueue()
		queue.Dequeue() // Не должно паниковать
	})

	t.Run("Удаление из очереди с одним элементом", func(t *testing.T) {
		queue := NewQueue()
		queue.Enqueue("единственный")
		queue.Dequeue()

		if queue.head != nil || queue.tail != nil {
			t.Error("Очередь должна быть пустой после удаления единственного элемента")
		}
	})

	t.Run("Удаление из очереди с несколькими элементами", func(t *testing.T) {
		queue := NewQueue()
		queue.Enqueue("первый")
		queue.Enqueue("второй")
		queue.Enqueue("третий")

		queue.Dequeue()
		if queue.head.value != "второй" {
			t.Error("Голова не обновилась после удаления")
		}
		if queue.head.next.value != "третий" {
			t.Error("Связи не обновлены корректно")
		}

		queue.Dequeue()
		if queue.head.value != "третий" {
			t.Error("Голова не обновилась после второго удаления")
		}
		if queue.tail != queue.head {
			t.Error("Голова и хвост должны быть одинаковыми для одного элемента")
		}

		queue.Dequeue()
		if queue.head != nil || queue.tail != nil {
			t.Error("Очередь должна быть пустой после удаления всех элементов")
		}
	})
}

func TestQueue_Getters(t *testing.T) {
	queue := NewQueue()

	t.Run("Получение головы пустой очереди", func(t *testing.T) {
		if queue.GetHead() != nil {
			t.Error("GetHead должен возвращать nil для пустой очереди")
		}
	})

	t.Run("Получение хвоста пустой очереди", func(t *testing.T) {
		if queue.GetTail() != nil {
			t.Error("GetTail должен возвращать nil для пустой очереди")
		}
	})

	t.Run("Получение головы непустой очереди", func(t *testing.T) {
		queue.Enqueue("элемент")
		if queue.GetHead() != queue.head {
			t.Error("GetHead возвращает неверное значение")
		}
	})

	t.Run("Получение хвоста непустой очереди", func(t *testing.T) {
		if queue.GetTail() != queue.tail {
			t.Error("GetTail возвращает неверное значение")
		}
	})
}

func TestQueue_IsEmpty(t *testing.T) {
	t.Run("Проверка пустой очереди", func(t *testing.T) {
		queue := NewQueue()
		if !queue.IsEmpty() {
			t.Error("Новая очередь должна быть пустой")
		}
	})

	t.Run("Проверка непустой очереди", func(t *testing.T) {
		queue := NewQueue()
		queue.Enqueue("элемент")
		if queue.IsEmpty() {
			t.Error("Очередь с элементами не должна быть пустой")
		}
	})

	t.Run("Проверка очереди после удаления всех элементов", func(t *testing.T) {
		queue := NewQueue()
		queue.Enqueue("элемент")
		queue.Dequeue()
		if !queue.IsEmpty() {
			t.Error("Очередь должна быть пустой после удаления всех элементов")
		}
	})
}

func TestQueue_Print(t *testing.T) {
	t.Run("Печать пустой очереди", func(t *testing.T) {
		queue := NewQueue()
		queue.Print()
	})

	t.Run("Печать непустой очереди", func(t *testing.T) {
		queue := NewQueue()
		queue.Enqueue("первый")
		queue.Enqueue("второй")
		queue.Print()
	})
}

// Дополнительные тесты для полного покрытия
func TestQueue_ComplexOperations(t *testing.T) {
	queue := NewQueue()

	// Серия операций Enqueue/Dequeue
	t.Run("Чередование добавления и удаления", func(t *testing.T) {
		queue.Enqueue("1")
		queue.Enqueue("2")
		queue.Dequeue()
		queue.Enqueue("3")
		queue.Dequeue()
		queue.Enqueue("4")

		if queue.head.value != "3" {
			t.Error("Некорректная работа при чередовании операций")
		}
		if queue.tail.value != "4" {
			t.Error("Хвост не обновляется корректно")
		}
		if queue.Length() != 2 {
			t.Error("Неверное количество элементов")
		}
	})
}

func (q *Queue) Length() int {
	count := 0
	current := q.head
	for current != nil {
		count++
		current = current.next
	}
	return count
}
