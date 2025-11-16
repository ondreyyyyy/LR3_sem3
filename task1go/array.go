package main

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

func (arr *DynArray) GetElement(index int) (string, error) {
	if index < 0 || index >= arr.size {
		return "", outOfRangeError("Индекс не является элементом массива.")
	}
	return arr.data[index], nil
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

type outOfRangeError string

func (e outOfRangeError) Error() string {
	return string(e)
}
