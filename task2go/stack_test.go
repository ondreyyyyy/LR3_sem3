package main

import (
	"testing"
)

func TestNewStack(t *testing.T) {
	t.Run("Создание нового стека", func(t *testing.T) {
		stack := NewStack()
		if stack == nil {
			t.Error("Конструктор вернул nil")
		}
		if stack.head != nil {
			t.Error("Голова стека должна быть nil при создании")
		}
	})
}

func TestStack_Push(t *testing.T) {
	stack := NewStack()

	t.Run("Добавление первого элемента", func(t *testing.T) {
		stack.Push("первый")
		if stack.head == nil {
			t.Error("Голова стека не установлена")
		}
		if stack.head.value != "первый" {
			t.Errorf("Ожидалось 'первый', получено '%s'", stack.head.value)
		}
	})

	t.Run("Добавление нескольких элементов", func(t *testing.T) {
		stack.Push("второй")
		stack.Push("третий")

		if stack.head.value != "третий" {
			t.Error("LIFO нарушен")
		}
		if stack.head.next.value != "второй" {
			t.Error("Связи между элементами нарушены")
		}
	})
}

func TestStack_Pop(t *testing.T) {
	t.Run("Извлечение из пустого стека", func(t *testing.T) {
		stack := NewStack()
		_, err := stack.Pop()
		if err == nil {
			t.Error("Ожидалась ошибка при извлечении из пустого стека")
		}
	})

	t.Run("Извлечение из непустого стека", func(t *testing.T) {
		stack := NewStack()
		stack.Push("первый")
		stack.Push("второй")

		val, err := stack.Pop()
		if err != nil {
			t.Error("Не ожидалась ошибка при извлечении")
		}
		if val != "второй" {
			t.Errorf("Ожидалось 'второй', получено '%s'", val)
		}
		if stack.head.value != "первый" {
			t.Error("Голова стека не обновилась после извлечения")
		}

		val, err = stack.Pop()
		if err != nil {
			t.Error("Не ожидалась ошибка при извлечении")
		}
		if val != "первый" {
			t.Errorf("Ожидалось 'первый', получено '%s'", val)
		}
		if stack.head != nil {
			t.Error("Стек должен быть пуст после извлечения всех элементов")
		}
	})
}

func TestStack_GetElement(t *testing.T) {
	stack := NewStack()
	stack.Push("нижний")
	stack.Push("средний")
	stack.Push("верхний")

	t.Run("Получение элемента по корректному индексу", func(t *testing.T) {
		val, err := stack.GetElement(0)
		if err != nil || val != "верхний" {
			t.Error("Не удалось получить элемент с индексом 0")
		}

		val, err = stack.GetElement(1)
		if err != nil || val != "средний" {
			t.Error("Не удалось получить элемент с индексом 1")
		}

		val, err = stack.GetElement(2)
		if err != nil || val != "нижний" {
			t.Error("Не удалось получить элемент с индексом 2")
		}
	})

	t.Run("Получение элемента с отрицательным индексом", func(t *testing.T) {
		_, err := stack.GetElement(-1)
		if err == nil {
			t.Error("Ожидалась ошибка для отрицательного индекса")
		}
	})

	t.Run("Получение элемента с индексом больше размера", func(t *testing.T) {
		_, err := stack.GetElement(10)
		if err == nil {
			t.Error("Ожидалась ошибка для индекса больше размера")
		}
	})
}

func TestStack_IsEmpty(t *testing.T) {
	t.Run("Проверка пустого стека", func(t *testing.T) {
		stack := NewStack()
		if !stack.IsEmpty() {
			t.Error("Новый стек должен быть пустым")
		}
	})

	t.Run("Проверка непустого стека", func(t *testing.T) {
		stack := NewStack()
		stack.Push("элемент")
		if stack.IsEmpty() {
			t.Error("Стек с элементами не должен быть пустым")
		}
	})

	t.Run("Проверка стека после извлечения всех элементов", func(t *testing.T) {
		stack := NewStack()
		stack.Push("элемент")
		stack.Pop()
		if !stack.IsEmpty() {
			t.Error("Стек должен быть пустым после извлечения всех элементов")
		}
	})
}

func TestStack_Print(t *testing.T) {
	t.Run("Печать пустого стека", func(t *testing.T) {
		stack := NewStack()
		stack.Print()
	})

	t.Run("Печать непустого стека", func(t *testing.T) {
		stack := NewStack()
		stack.Push("первый")
		stack.Push("второй")
		stack.Print()
	})
}

func TestStack_Destroy(t *testing.T) {
	t.Run("Уничтожение стека", func(t *testing.T) {
		stack := NewStack()
		stack.Push("элемент1")
		stack.Push("элемент2")

		stack.Destroy()
		if stack.head != nil {
			t.Error("Стек не уничтожен корректно")
		}
	})
}
