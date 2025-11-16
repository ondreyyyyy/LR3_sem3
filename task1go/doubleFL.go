package main

import "fmt"

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
