package main

import "fmt"

type FNode struct {
	value string
	next  *FNode
}

type ForwardList struct {
	head *FNode
	tail *FNode
}

// Конструктор
func NewForwardList(data string) *ForwardList {
	firstNode := &FNode{value: data, next: nil}
	return &ForwardList{
		head: firstNode,
		tail: firstNode,
	}
}

// Основные методы
func (fl *ForwardList) AddAtHead(data string) {
	if fl.head == nil {
		fl.head = &FNode{value: data, next: nil}
		fl.tail = fl.head
	} else {
		newHead := &FNode{value: data, next: fl.head}
		fl.head = newHead
	}
}

func (fl *ForwardList) AddAtTail(data string) {
	if fl.head == nil {
		fl.head = &FNode{value: data, next: nil}
		fl.tail = fl.head
	} else {
		newNode := &FNode{value: data, next: nil}
		fl.tail.next = newNode
		fl.tail = newNode
	}
}

func (fl *ForwardList) SearchNode(targetValue string) {
	if fl.head == nil {
		fmt.Println("Список пуст.")
		return
	}

	isFound := false
	curElem := fl.head
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
	} else {
		fmt.Printf("Элемент %s найден. Индекс: %d\n", targetValue, index)
		return
	}
}

func (fl *ForwardList) AddBeforeIndex(data string, index int) {
	if fl.head == nil {
		fmt.Println("Список пуст.")
		return
	} else if index == 0 {
		fl.AddAtHead(data)
		return
	} else if index < 0 {
		fmt.Println("Неверный индекс!")
		return
	}

	i := 0
	curElem := fl.head

	for i != index-1 && curElem != nil {
		curElem = curElem.next
		i++
	}

	if curElem == nil {
		fmt.Println("Элемента с таким индексом не существует!")
		return
	}

	newNode := &FNode{value: data, next: curElem.next}
	curElem.next = newNode
}

func (fl *ForwardList) AddAfterIndex(data string, index int) {
	if fl.head == nil {
		fmt.Println("Список пуст.")
		return
	} else if index < 0 {
		fmt.Println("Неверный индекс!")
		return
	}

	curElem := fl.head
	i := 0

	for i != index && curElem != nil {
		curElem = curElem.next
		i++
	}

	if curElem == nil {
		fmt.Println("Элемента с таким индексом не существует!")
		return
	}

	newNode := &FNode{value: data, next: curElem.next}
	curElem.next = newNode

	if curElem == fl.tail {
		fl.tail = newNode
	}
}

func (fl *ForwardList) DeleteAtHead() {
	if fl.head == nil {
		fmt.Println("Нечего удалять.")
		return
	}

	fl.head = fl.head.next

	if fl.head == nil {
		fl.tail = nil
	}
}

func (fl *ForwardList) DeleteAtTail() {
	if fl.head == nil {
		fmt.Println("Список пуст.")
		return
	} else if fl.head == fl.tail {
		fl.DeleteAtHead()
		return
	}

	curElem := fl.head

	for curElem.next != fl.tail {
		curElem = curElem.next
	}

	fl.tail = curElem
	fl.tail.next = nil
}

func (fl *ForwardList) DeleteBeforeIndex(index int) {
	if fl.head == nil || fl.head == fl.tail {
		fmt.Println("Удаление невозможно.")
		return
	} else if index == 1 {
		fl.DeleteAtHead()
		return
	} else if index <= 0 {
		fmt.Println("Неверный индекс.")
		return
	}

	curElem := fl.head
	i := 0

	for i != index-2 && curElem != nil {
		curElem = curElem.next
		i++
	}

	if curElem == nil || curElem == fl.tail || curElem.next == nil {
		fmt.Println("Неверный индекс.")
		return
	}

	deleteNode := curElem.next
	curElem.next = deleteNode.next
}

func (fl *ForwardList) DeleteAfterIndex(index int) {
	if fl.head == nil || fl.head == fl.tail {
		fmt.Println("Удаление невозможно.")
		return
	} else if index < 0 {
		fmt.Println("Неверный индекс.")
		return
	}

	curElem := fl.head
	i := 0

	for i != index && curElem != nil {
		curElem = curElem.next
		i++
	}

	if curElem == nil || curElem == fl.tail {
		fmt.Println("Неверный индекс.")
		return
	}

	if curElem.next == fl.tail {
		fl.DeleteAtTail()
		return
	}

	deleteNode := curElem.next
	curElem.next = deleteNode.next

	if deleteNode == fl.tail {
		fl.tail = curElem
	}
}

func (fl *ForwardList) DeleteValue(data string) {
	if fl.head == nil {
		fmt.Println("Удаление невозможно.")
		return
	}

	curElem := fl.head
	var prevElem *FNode = nil
	isFound := false

	for curElem != nil {
		if curElem.value == data {
			isFound = true
			break
		}
		prevElem = curElem
		curElem = curElem.next
	}

	if !isFound {
		fmt.Println("Элемент не найден.")
		return
	}

	if curElem == fl.head {
		fl.DeleteAtHead()
	} else if curElem == fl.tail {
		fl.DeleteAtTail()
	} else {
		prevElem.next = curElem.next
	}
}

// Геттеры
func (fl *ForwardList) GetHead() *FNode {
	return fl.head
}

func (fl *ForwardList) GetTail() *FNode {
	return fl.tail
}

func (fl *ForwardList) IsEmpty() bool {
	return fl.head == nil
}

func (fl *ForwardList) Print() {
	fmt.Print("Односвязный список: ")

	current := fl.head
	for current != nil {
		fmt.Print(current.value + " ")
		current = current.next
	}
	fmt.Println()
}
