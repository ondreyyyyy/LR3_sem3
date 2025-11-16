package main

import (
	"fmt"
	"strconv"
)

type HANode struct {
	key       string
	data      string
	isDeleted bool
	isEmpty   bool
}

type HashA struct {
	table    []HANode
	capacity int
	size     int
}

// Конструктор
func NewHashATable() *HashA {
	capacity := 8
	table := make([]HANode, capacity)
	for i := 0; i < capacity; i++ {
		table[i].isDeleted = false
		table[i].isEmpty = true
	}

	return &HashA{
		table:    table,
		capacity: capacity,
		size:     0,
	}
}

// Хэш-функция
func (h *HashA) hashaFunc(key string) int {
	hash := 0
	for _, c := range key {
		hash = (hash*47 + int(c)) % h.capacity
	}
	return hash % h.capacity
}

// Рехэширование
func (h *HashA) rehash() {
	oldCapacity := h.capacity
	oldTable := h.table

	h.capacity = oldCapacity * 2
	h.table = make([]HANode, h.capacity)
	h.size = 0

	for i := 0; i < h.capacity; i++ {
		h.table[i].isEmpty = true
		h.table[i].isDeleted = false
	}

	for i := 0; i < oldCapacity; i++ {
		if !oldTable[i].isEmpty && !oldTable[i].isDeleted {
			j := 0
			index := h.hashaFunc(oldTable[i].key)
			originalIndex := index

			for j < h.capacity {
				if h.table[index].isEmpty {
					h.table[index].key = oldTable[i].key
					h.table[index].data = oldTable[i].data
					h.table[index].isDeleted = false
					h.table[index].isEmpty = false
					h.size++
					break
				}
				j++
				index = (originalIndex + j) % h.capacity
			}
		}
	}

	fmt.Printf("Требуется рехэширование, старый размер: %d, новый размер: %d\n", oldCapacity, h.capacity)
}

// Добавление элемента
func (h *HashA) AddElement(key string, data string) {
	i := 0
	if h.size >= h.capacity*3/4 {
		h.rehash()
	}

	index := h.hashaFunc(key)
	originalIndex := index

	for !h.table[index].isEmpty && !h.table[index].isDeleted {
		if h.table[index].key == key {
			h.table[index].data = data
			return
		}
		i++
		index = (originalIndex + i) % h.capacity

		if i == h.capacity {
			fmt.Println("Нет места для вставки.")
			return
		}
	}

	h.table[index].key = key
	h.table[index].data = data
	h.table[index].isDeleted = false
	h.table[index].isEmpty = false
	h.size++
}

// Поиск элемента (возвращает int)
func (h *HashA) FindElement(key string) int {
	i := 0
	index := h.hashaFunc(key)
	originalIndex := index

	for i < h.capacity {
		if h.table[index].isEmpty && !h.table[index].isDeleted {
			return -1
		}

		if !h.table[index].isEmpty && !h.table[index].isDeleted {
			if h.table[index].key == key {
				result, err := strconv.Atoi(h.table[index].data)
				if err != nil {
					return -1
				}
				return result
			}
		}

		i++
		index = (originalIndex + i) % h.capacity
	}

	return -1
}

// Поиск элемента (возвращает string)
func (h *HashA) FindElementStr(key string) string {
	i := 0
	index := h.hashaFunc(key)
	originalIndex := index

	for i < h.capacity {
		if h.table[index].isEmpty && !h.table[index].isDeleted {
			return "-1"
		}

		if !h.table[index].isEmpty && !h.table[index].isDeleted {
			if h.table[index].key == key {
				return h.table[index].data
			}
		}

		i++
		index = (originalIndex + i) % h.capacity
	}

	return "-1"
}

// Удаление элемента
func (h *HashA) DeleteElement(key string) {
	i := 0
	index := h.hashaFunc(key)
	originalIndex := index

	for i < h.capacity {
		if h.table[index].isEmpty && !h.table[index].isDeleted {
			break
		}

		if !h.table[index].isEmpty && !h.table[index].isDeleted {
			if h.table[index].key == key {
				h.table[index].isDeleted = true
				h.size--
				fmt.Println("Элемент удален.")
				return
			}
		}

		i++
		index = (originalIndex + i) % h.capacity
	}

	fmt.Println("Элемент не найден!")
}

// Печать таблицы
func (h *HashA) PrintHashTable() {
	fmt.Printf("Хэш-таблица, размер: %d, вместимость: %d):\n", h.size, h.capacity)

	for i := 0; i < h.capacity; i++ {
		fmt.Printf("Ячейка %d: ", i)

		if h.table[i].isEmpty {
			if h.table[i].isDeleted {
				fmt.Print("[УДАЛЕНО]")
			} else {
				fmt.Print("пусто")
			}
		} else {
			fmt.Printf("[%s -> %s]", h.table[i].key, h.table[i].data)
			if h.table[i].isDeleted {
				fmt.Print(" (удалено)")
			}
		}
		fmt.Println()
	}
}
