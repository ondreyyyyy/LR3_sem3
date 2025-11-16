package main

import (
	"encoding/binary"
	"fmt"
	"io"
)

type DNode struct {
	value string
	next  *DNode
	prev  *DNode
}

type DoubleFL struct {
	head *DNode
	tail *DNode
}

// Конструктор
func NewDoubleFL(beginNode string) *DoubleFL {
	node := &DNode{value: beginNode}
	return &DoubleFL{
		head: node,
		tail: node,
	}
}

// Основные методы
func (dfl *DoubleFL) AddAtHead(data string) {
	if dfl.head == nil {
		node := &DNode{value: data}
		dfl.head = node
		dfl.tail = node
		return
	}

	newHead := &DNode{value: data, next: dfl.head}
	dfl.head.prev = newHead
	dfl.head = newHead
}

func (dfl *DoubleFL) AddAtTail(data string) {
	if dfl.head == nil {
		node := &DNode{value: data}
		dfl.head = node
		dfl.tail = node
		return
	}

	newNode := &DNode{value: data, prev: dfl.tail}
	dfl.tail.next = newNode
	dfl.tail = newNode
}

func (dfl *DoubleFL) AddBeforeIndex(data string, index int) {
	if dfl.head == nil {
		fmt.Println("Список пуст.")
		return
	} else if index == 0 {
		dfl.AddAtHead(data)
		return
	} else if index < 0 {
		fmt.Println("Неверный индекс!")
		return
	}

	i := 0
	curElem := dfl.head

	for i != index && curElem != nil {
		curElem = curElem.next
		i++
	}

	if curElem == nil {
		fmt.Println("Элемента с таким индексом не существует!")
		return
	}

	newNode := &DNode{value: data, next: curElem, prev: curElem.prev}
	curElem.prev.next = newNode
	curElem.prev = newNode
}

func (dfl *DoubleFL) AddAfterIndex(data string, index int) {
	if dfl.head == nil {
		fmt.Println("Список пуст.")
		return
	} else if index < 0 {
		fmt.Println("Неверный индекс!")
		return
	}

	curElem := dfl.head
	i := 0

	for i != index && curElem != nil {
		curElem = curElem.next
		i++
	}

	if curElem == nil {
		fmt.Println("Элемента с таким индексом не существует!")
		return
	}

	if curElem == dfl.tail {
		dfl.AddAtTail(data)
		return
	}

	newNode := &DNode{value: data, next: curElem.next, prev: curElem}
	curElem.next.prev = newNode
	curElem.next = newNode
}

func (dfl *DoubleFL) DeleteAtHead() {
	if dfl.head == nil {
		fmt.Println("Список пуст.")
		return
	}

	if dfl.head == dfl.tail {
		dfl.head = nil
		dfl.tail = nil
	} else {
		dfl.head = dfl.head.next
		dfl.head.prev = nil
	}
}

func (dfl *DoubleFL) DeleteAtTail() {
	if dfl.head == nil {
		fmt.Println("Список пуст.")
		return
	}

	if dfl.head == dfl.tail {
		dfl.head = nil
		dfl.tail = nil
	} else {
		dfl.tail.prev.next = nil
		dfl.tail = dfl.tail.prev
	}
}

func (dfl *DoubleFL) DeleteBeforeIndex(index int) {
	if dfl.head == nil || dfl.head == dfl.tail {
		fmt.Println("Удаление невозможно.")
		return
	} else if index == 1 {
		dfl.DeleteAtHead()
		return
	} else if index <= 0 {
		fmt.Println("Неверный индекс.")
		return
	}

	curElem := dfl.head
	i := 0

	for i != index && curElem != nil {
		curElem = curElem.next
		i++
	}

	if curElem == nil || curElem.prev == nil {
		fmt.Println("Неверный индекс.")
		return
	}

	deleteNode := curElem.prev

	if deleteNode == dfl.head {
		dfl.DeleteAtHead()
		return
	}

	deleteNode.prev.next = curElem
	curElem.prev = deleteNode.prev
}

func (dfl *DoubleFL) DeleteAfterIndex(index int) {
	if dfl.head == nil || dfl.head == dfl.tail {
		fmt.Println("Удаление невозможно.")
		return
	} else if index < 0 {
		fmt.Println("Неверный индекс.")
		return
	}

	curElem := dfl.head
	i := 0

	for i != index && curElem != nil {
		curElem = curElem.next
		i++
	}

	if curElem == nil || curElem == dfl.tail {
		fmt.Println("Неверный индекс.")
		return
	}

	if curElem.next == dfl.tail {
		dfl.DeleteAtTail()
		return
	}

	deleteNode := curElem.next
	curElem.next = deleteNode.next
	deleteNode.next.prev = curElem
}

func (dfl *DoubleFL) DeleteValue(targetValue string) {
	if dfl.head == nil {
		fmt.Println("Список пуст.")
		return
	}

	curElem := dfl.head
	isFound := false

	for curElem != nil {
		if curElem.value == targetValue {
			isFound = true
			break
		}
		curElem = curElem.next
	}

	if !isFound {
		fmt.Println("Элемент не найден.")
		return
	}

	if curElem == dfl.head {
		dfl.DeleteAtHead()
		return
	}

	if curElem == dfl.tail {
		dfl.DeleteAtTail()
		return
	}

	deleteNode := curElem
	deleteNode.prev.next = deleteNode.next
	deleteNode.next.prev = deleteNode.prev
}

func (dfl *DoubleFL) SearchValue(targetValue string) {
	if dfl.head == nil {
		fmt.Println("Список пуст.")
		return
	}

	curElem := dfl.head
	isFound := false
	index := 0

	for curElem != nil {
		if curElem.value == targetValue {
			isFound = true
			break
		}
		curElem = curElem.next
		index++
	}

	if !isFound {
		fmt.Println("Элемент не найден.")
		return
	}

	fmt.Printf("Элемент %s найден. Индекс: %d\n", curElem.value, index)
}

// Геттеры
func (dfl *DoubleFL) GetHead() *DNode {
	return dfl.head
}

func (dfl *DoubleFL) GetTail() *DNode {
	return dfl.tail
}

func (dfl *DoubleFL) IsEmpty() bool {
	return dfl.head == nil
}

func (dfl *DoubleFL) Print() {
	fmt.Print("Двусвязный список: ")

	if dfl.head == nil {
		fmt.Println("Список пуст")
		return
	}

	current := dfl.head
	for current != nil {
		fmt.Print(current.value + " ")
		current = current.next
	}
	fmt.Println()
}

func (dfl *DoubleFL) SerializeToText(w io.Writer) error {
	// Считаем количество элементов
	count := 0
	current := dfl.head
	for current != nil {
		count++
		current = current.next
	}

	_, err := fmt.Fprintf(w, "DOUBLELIST %d", count)
	if err != nil {
		return err
	}

	// Записываем элементы
	current = dfl.head
	for current != nil {
		_, err = fmt.Fprintf(w, " %s", current.value)
		if err != nil {
			return err
		}
		current = current.next
	}
	_, err = fmt.Fprintln(w)
	return err
}

// Десериализация из текстового файла
func (dfl *DoubleFL) DeserializeFromText(r io.Reader) error {
	var count int
	_, err := fmt.Fscanf(r, "DOUBLELIST %d", &count)
	if err != nil {
		return err
	}

	if count == 0 {
		dfl.head = nil
		dfl.tail = nil
		return nil
	}

	// Читаем первый элемент
	var firstValue string
	_, err = fmt.Fscanf(r, "%s", &firstValue)
	if err != nil {
		return err
	}

	dfl.head = &DNode{value: firstValue, next: nil, prev: nil}
	dfl.tail = dfl.head
	current := dfl.head

	// Читаем остальные элементы
	for i := 1; i < count; i++ {
		var value string
		_, err = fmt.Fscanf(r, "%s", &value)
		if err != nil {
			return err
		}

		newNode := &DNode{value: value, next: nil, prev: current}
		current.next = newNode
		dfl.tail = newNode
		current = newNode
	}

	// Читаем оставшийся перевод строки
	var newline string
	fmt.Fscanf(r, "%s", &newline)

	return nil
}

// Сериализация в бинарный файл
func (dfl *DoubleFL) SerializeToBinary(w io.Writer) error {
	// Записываем тип структуры (3 = DOUBLELIST)
	binary.Write(w, binary.LittleEndian, int32(3))

	// Считаем количество элементов
	count := 0
	current := dfl.head
	for current != nil {
		count++
		current = current.next
	}

	binary.Write(w, binary.LittleEndian, int32(count))

	// Записываем элементы
	current = dfl.head
	for current != nil {
		strBytes := []byte(current.value)
		binary.Write(w, binary.LittleEndian, int32(len(strBytes)))
		binary.Write(w, binary.LittleEndian, strBytes)
		current = current.next
	}

	return nil
}

// Десериализация из бинарного файла
func (dfl *DoubleFL) DeserializeFromBinary(r io.Reader) error {
	var count int32
	err := binary.Read(r, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	if count == 0 {
		dfl.head = nil
		dfl.tail = nil
		return nil
	}

	// Читаем первый элемент
	var firstStrLen int32
	err = binary.Read(r, binary.LittleEndian, &firstStrLen)
	if err != nil {
		return err
	}

	firstBytes := make([]byte, firstStrLen)
	err = binary.Read(r, binary.LittleEndian, &firstBytes)
	if err != nil {
		return err
	}

	dfl.head = &DNode{value: string(firstBytes), next: nil, prev: nil}
	dfl.tail = dfl.head
	current := dfl.head

	// Читаем остальные элементы
	for i := 1; i < int(count); i++ {
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

		newNode := &DNode{value: string(strBytes), next: nil, prev: current}
		current.next = newNode
		dfl.tail = newNode
		current = newNode
	}

	return nil
}
