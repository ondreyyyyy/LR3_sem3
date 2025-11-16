package main

import (
	"encoding/binary"
	"fmt"
	"io"
)

type DynArray struct {
	data     []string
	size     int
	capacity int
}

// Конструктор
func NewDynArray(initialCapacity int) *DynArray {
	if initialCapacity <= 0 {
		initialCapacity = 1
	}
	return &DynArray{
		size:     0,
		capacity: initialCapacity,
		data:     make([]string, initialCapacity),
	}
}

// Основные методы
func (arr *DynArray) AddAtIndex(index int, data string) {
	if index < 0 || index > arr.size {
		return
	}

	if arr.size == arr.capacity {
		arr.resize(arr.capacity * 2)
	}

	if arr.size == arr.capacity {
		newCapacity := arr.capacity * 2
		newData := make([]string, newCapacity)

		for i := 0; i < index; i++ {
			newData[i] = arr.data[i]
		}

		newData[index] = data

		for i := index; i < arr.size; i++ {
			newData[i+1] = arr.data[i]
		}

		arr.data = newData
		arr.capacity = newCapacity
	} else {
		for i := arr.size; i > index; i-- {
			arr.data[i] = arr.data[i-1]
		}
		arr.data[index] = data
	}

	arr.size++
}

func (arr *DynArray) PushBack(data string) {
	arr.AddAtIndex(arr.size, data)
}

func (arr *DynArray) GetElement(index int) string {
	if index < 0 || index >= arr.size {
		return ""
	}
	return arr.data[index]
}

func (arr *DynArray) RemoveFromIndex(index int) {
	if index < 0 || index >= arr.size {
		return
	}

	for i := index; i < arr.size-1; i++ {
		arr.data[i] = arr.data[i+1]
	}

	arr.size--
}

func (arr *DynArray) ReplaceElement(index int, data string) {
	if index < 0 || index >= arr.size {
		return
	}
	arr.data[index] = data
}

// Геттеры
func (arr *DynArray) Length() int {
	return arr.size
}

func (arr *DynArray) Capacity() int {
	return arr.capacity
}

// Приватный метод
func (arr *DynArray) resize(newCapacity int) {
	newData := make([]string, newCapacity)
	copy(newData, arr.data)
	arr.data = newData
	arr.capacity = newCapacity
}

func (arr *DynArray) Print() {
	if arr.size == 0 {
		println("Массив пуст.")
		return
	}

	for i := 0; i < arr.size; i++ {
		print(arr.data[i] + " ")
	}
	println()
}

func (arr *DynArray) SerializeToText(w io.Writer) error {
	_, err := fmt.Fprintf(w, "ARRAY %d %d", arr.size, arr.capacity)
	if err != nil {
		return err
	}

	for i := 0; i < arr.size; i++ {
		_, err = fmt.Fprintf(w, " %s", arr.data[i])
		if err != nil {
			return err
		}
	}
	_, err = fmt.Fprintln(w)
	return err
}

// Десериализация из текстового файла
func (arr *DynArray) DeserializeFromText(r io.Reader) error {
	var size, capacity int
	_, err := fmt.Fscanf(r, "ARRAY %d %d", &size, &capacity)
	if err != nil {
		return err
	}

	arr.size = size
	arr.capacity = capacity
	arr.data = make([]string, capacity)

	for i := 0; i < size; i++ {
		_, err = fmt.Fscanf(r, "%s", &arr.data[i])
		if err != nil {
			return err
		}
	}

	// Читаем оставшийся перевод строки
	var newline string
	fmt.Fscanf(r, "%s", &newline)

	return nil
}

// Сериализация в бинарный файл
func (arr *DynArray) SerializeToBinary(w io.Writer) error {
	// Записываем тип структуры (1 = ARRAY)
	binary.Write(w, binary.LittleEndian, int32(1))

	// Записываем размер и вместимость
	binary.Write(w, binary.LittleEndian, int32(arr.size))
	binary.Write(w, binary.LittleEndian, int32(arr.capacity))

	// Записываем элементы
	for i := 0; i < arr.size; i++ {
		strBytes := []byte(arr.data[i])
		binary.Write(w, binary.LittleEndian, int32(len(strBytes)))
		binary.Write(w, binary.LittleEndian, strBytes)
	}

	return nil
}

// Десериализация из бинарного файла
func (arr *DynArray) DeserializeFromBinary(r io.Reader) error {
	var size, capacity int32
	err := binary.Read(r, binary.LittleEndian, &size)
	if err != nil {
		return err
	}

	err = binary.Read(r, binary.LittleEndian, &capacity)
	if err != nil {
		return err
	}

	arr.size = int(size)
	arr.capacity = int(capacity)
	arr.data = make([]string, capacity)

	for i := 0; i < int(size); i++ {
		var strLen int32
		err = binary.Read(r, binary.LittleEndian, &strLen)
		if err != nil {
			return err
		}

		strBytes := make([]byte, strLen)
		err = binary.Read(r, binary.LittleEndian, &strBytes)
		if err != nil {
			return err
		}

		arr.data[i] = string(strBytes)
	}

	return nil
}
