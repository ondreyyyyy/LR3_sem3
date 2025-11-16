package main

import "fmt"

type HNode struct {
	key  string
	data int
	next *HNode
	prev *HNode
}

type Hash struct {
	table    []*HNode
	size     int
	capacity int
}

// Конструктор
func NewHashTable() *Hash {
	capacity := 8
	table := make([]*HNode, capacity)
	return &Hash{
		table:    table,
		size:     0,
		capacity: capacity,
	}
}

// Хэш-функция
func (h *Hash) hashFunc(key string) int {
	hash := 0
	for _, c := range key {
		hash = (hash*47 + int(c)) % h.capacity
	}
	return hash % h.capacity
}

// Добавление элемента
func (h *Hash) AddElement(key string, data int) {
	index := h.hashFunc(key)
	begin := h.table[index]
	curElem := begin

	for curElem != nil {
		if curElem.key == key {
			curElem.data = data
			return
		}
		curElem = curElem.next
	}

	addNode := &HNode{
		key:  key,
		data: data,
		next: begin,
		prev: nil,
	}

	if h.table[index] != nil {
		h.table[index].prev = addNode
	}

	h.table[index] = addNode
	h.size++
}

// Поиск элемента
func (h *Hash) FindElement(key string) int {
	index := h.hashFunc(key)
	begin := h.table[index]
	curElem := begin

	for curElem != nil {
		if curElem.key == key {
			return curElem.data
		}
		curElem = curElem.next
	}

	return -1
}

// Удаление элемента
func (h *Hash) DeleteElement(key string) {
	index := h.hashFunc(key)
	deleteNode := h.table[index]

	for deleteNode != nil {
		if deleteNode.key == key {
			if deleteNode.prev != nil {
				deleteNode.prev.next = deleteNode.next
			} else {
				h.table[index] = deleteNode.next
			}
			if deleteNode.next != nil {
				deleteNode.next.prev = deleteNode.prev
			}
			h.size--
			return
		}
		deleteNode = deleteNode.next
	}
}

// Печать таблицы
func (h *Hash) PrintHashTable() {
	fmt.Printf("Хэш-таблица (элементов: %d, вместимость: %d):\n", h.size, h.capacity)

	for i := 0; i < h.capacity; i++ {
		fmt.Printf("Цепочка %d: ", i)

		current := h.table[i]
		if current == nil {
			fmt.Print("пусто")
		} else {
			for current != nil {
				fmt.Printf("[%s -> %d]", current.key, current.data)
				if current.next != nil {
					fmt.Print(" -> ")
				}
				current = current.next
			}
		}
		fmt.Println()
	}
}
