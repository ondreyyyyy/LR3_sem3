package main

import "fmt"

type QNode struct {
	value string
	next  *QNode
}

type Queue struct {
	head *QNode
	tail *QNode
}

// Конструктор
func NewQueue() *Queue {
	return &Queue{head: nil, tail: nil}
}

// Основные методы
func (q *Queue) Enqueue(data string) {
	newNode := &QNode{value: data, next: nil}
	if q.head == nil {
		q.head = newNode
		q.tail = newNode
		return
	}

	q.tail.next = newNode
	q.tail = newNode
}

func (q *Queue) Dequeue() {
	if q.head == nil {
		fmt.Println("Очередь пустая. Нечего удалять.")
		return
	}

	if q.head == q.tail {
		q.head = nil
		q.tail = nil
	} else {
		q.head = q.head.next
	}
}

// Геттеры
func (q *Queue) GetHead() *QNode {
	return q.head
}

func (q *Queue) GetTail() *QNode {
	return q.tail
}

func (q *Queue) IsEmpty() bool {
	return q.head == nil
}

func (q *Queue) Print() {
	if q.head == nil {
		fmt.Println("Очередь пуста.")
		return
	}

	fmt.Print("Очередь: ")
	curElem := q.head
	for curElem != nil {
		fmt.Print(curElem.value + " ")
		curElem = curElem.next
	}
	fmt.Println()
}
