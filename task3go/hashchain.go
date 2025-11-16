package main

import (
	"encoding/binary"
	"fmt"
	"io"
)

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

func NewHashTable() *Hash {
	capacity := 8
	table := make([]*HNode, capacity)
	return &Hash{
		table:    table,
		size:     0,
		capacity: capacity,
	}
}

func (h *Hash) hashFunc(key string) int {
	hash := 0
	for _, c := range key {
		hash = (hash*47 + int(c)) % h.capacity
	}
	return hash % h.capacity
}

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
func (h *Hash) SerializeToText(w io.Writer) error {
	_, err := fmt.Fprintf(w, "HASH %d %d", h.capacity, h.size)
	if err != nil {
		return err
	}

	// Записываем все элементы
	for i := 0; i < h.capacity; i++ {
		current := h.table[i]
		for current != nil {
			_, err = fmt.Fprintf(w, " %d %s %d", i, current.key, current.data)
			if err != nil {
				return err
			}
			current = current.next
		}
	}
	_, err = fmt.Fprintln(w)
	return err
}

// Десериализация из текстового файла
func (h *Hash) DeserializeFromText(r io.Reader) error {
	var capacity, size int
	_, err := fmt.Fscanf(r, "HASH %d %d", &capacity, &size)
	if err != nil {
		return err
	}

	h.capacity = capacity
	h.size = size
	h.table = make([]*HNode, capacity)

	// Читаем элементы
	for i := 0; i < size; i++ {
		var index int
		var key string
		var data int
		_, err := fmt.Fscanf(r, "%d %s %d", &index, &key, &data)
		if err != nil {
			return err
		}

		if index < capacity {
			// Добавляем элемент в цепочку
			newNode := &HNode{
				key:  key,
				data: data,
				next: h.table[index],
				prev: nil,
			}

			if h.table[index] != nil {
				h.table[index].prev = newNode
			}

			h.table[index] = newNode
		}
	}

	// Читаем оставшийся перевод строки
	var newline string
	fmt.Fscanf(r, "%s", &newline)

	return nil
}

// Сериализация в бинарный файл
func (h *Hash) SerializeToBinary(w io.Writer) error {
	// Записываем тип структуры (7 = HASH)
	binary.Write(w, binary.LittleEndian, int32(7))

	binary.Write(w, binary.LittleEndian, int32(h.capacity))
	binary.Write(w, binary.LittleEndian, int32(h.size))

	// Записываем все элементы
	for i := 0; i < h.capacity; i++ {
		current := h.table[i]
		for current != nil {
			// Записываем индекс
			binary.Write(w, binary.LittleEndian, int32(i))

			// Записываем ключ
			keyBytes := []byte(current.key)
			binary.Write(w, binary.LittleEndian, int32(len(keyBytes)))
			binary.Write(w, binary.LittleEndian, keyBytes)

			// Записываем данные
			binary.Write(w, binary.LittleEndian, int32(current.data))

			current = current.next
		}
	}

	return nil
}

// Десериализация из бинарного файла
func (h *Hash) DeserializeFromBinary(r io.Reader) error {
	var capacity, size int32
	err := binary.Read(r, binary.LittleEndian, &capacity)
	if err != nil {
		return err
	}

	err = binary.Read(r, binary.LittleEndian, &size)
	if err != nil {
		return err
	}

	h.capacity = int(capacity)
	h.size = int(size)
	h.table = make([]*HNode, capacity)

	// Читаем элементы
	for i := 0; i < int(size); i++ {
		var index int32
		err = binary.Read(r, binary.LittleEndian, &index)
		if err != nil {
			return err
		}

		// Читаем ключ
		var keyLen int32
		err = binary.Read(r, binary.LittleEndian, &keyLen)
		if err != nil {
			return err
		}

		keyBytes := make([]byte, keyLen)
		err = binary.Read(r, binary.LittleEndian, &keyBytes)
		if err != nil {
			return err
		}

		// Читаем данные
		var data int32
		err = binary.Read(r, binary.LittleEndian, &data)
		if err != nil {
			return err
		}

		if int(index) < h.capacity {
			// Добавляем элемент в цепочку
			newNode := &HNode{
				key:  string(keyBytes),
				data: int(data),
				next: h.table[index],
				prev: nil,
			}

			if h.table[index] != nil {
				h.table[index].prev = newNode
			}

			h.table[index] = newNode
		}
	}

	return nil
}
