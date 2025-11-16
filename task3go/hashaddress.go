package main

import (
	"encoding/binary"
	"fmt"
	"io"
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
func (h *HashA) SerializeToText(w io.Writer) error {
	_, err := fmt.Fprintf(w, "HASHA %d %d", h.capacity, h.size)
	if err != nil {
		return err
	}

	// Записываем только непустые и неудаленные элементы
	for i := 0; i < h.capacity; i++ {
		if !h.table[i].isEmpty && !h.table[i].isDeleted {
			_, err = fmt.Fprintf(w, " %d %s %s", i, h.table[i].key, h.table[i].data)
			if err != nil {
				return err
			}
		}
	}
	_, err = fmt.Fprintln(w)
	return err
}

// Десериализация из текстового файла
func (h *HashA) DeserializeFromText(r io.Reader) error {
	var capacity, size int
	_, err := fmt.Fscanf(r, "HASHA %d %d", &capacity, &size)
	if err != nil {
		return err
	}

	h.capacity = capacity
	h.size = size
	h.table = make([]HANode, capacity)
	for i := 0; i < capacity; i++ {
		h.table[i].isEmpty = true
		h.table[i].isDeleted = false
	}

	// Читаем элементы
	for i := 0; i < size; i++ {
		var index int
		var key, data string
		_, err := fmt.Fscanf(r, "%d %s %s", &index, &key, &data)
		if err != nil {
			return err
		}

		if index < capacity {
			h.table[index].key = key
			h.table[index].data = data
			h.table[index].isEmpty = false
			h.table[index].isDeleted = false
		}
	}

	// Читаем оставшийся перевод строки
	var newline string
	fmt.Fscanf(r, "%s", &newline)

	return nil
}

// Сериализация в бинарный файл
func (h *HashA) SerializeToBinary(w io.Writer) error {
	// Записываем тип структуры (6 = HASHA)
	binary.Write(w, binary.LittleEndian, int32(6))

	binary.Write(w, binary.LittleEndian, int32(h.capacity))
	binary.Write(w, binary.LittleEndian, int32(h.size))

	// Записываем только непустые и неудаленные элементы
	for i := 0; i < h.capacity; i++ {
		if !h.table[i].isEmpty && !h.table[i].isDeleted {
			// Записываем индекс
			binary.Write(w, binary.LittleEndian, int32(i))

			// Записываем ключ
			keyBytes := []byte(h.table[i].key)
			binary.Write(w, binary.LittleEndian, int32(len(keyBytes)))
			binary.Write(w, binary.LittleEndian, keyBytes)

			// Записываем данные
			dataBytes := []byte(h.table[i].data)
			binary.Write(w, binary.LittleEndian, int32(len(dataBytes)))
			binary.Write(w, binary.LittleEndian, dataBytes)
		}
	}

	return nil
}

// Десериализация из бинарного файла
func (h *HashA) DeserializeFromBinary(r io.Reader) error {
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
	h.table = make([]HANode, capacity)
	for i := 0; i < int(capacity); i++ {
		h.table[i].isEmpty = true
		h.table[i].isDeleted = false
	}

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
		var dataLen int32
		err = binary.Read(r, binary.LittleEndian, &dataLen)
		if err != nil {
			return err
		}

		dataBytes := make([]byte, dataLen)
		err = binary.Read(r, binary.LittleEndian, &dataBytes)
		if err != nil {
			return err
		}

		if int(index) < h.capacity {
			h.table[index].key = string(keyBytes)
			h.table[index].data = string(dataBytes)
			h.table[index].isEmpty = false
			h.table[index].isDeleted = false
		}
	}

	return nil
}
