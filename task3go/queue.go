package main

import (
	"encoding/binary"
	"fmt"
	"io"
)

type QNode struct {
	value string
	next  *QNode
}

type Queue struct {
	head *QNode
	tail *QNode
}

func NewQueue() *Queue {
	return &Queue{head: nil, tail: nil}
}

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

func (q *Queue) SerializeToText(w io.Writer) error {
	// Считаем количество элементов
	count := 0
	current := q.head
	for current != nil {
		count++
		current = current.next
	}

	_, err := fmt.Fprintf(w, "QUEUE %d", count)
	if err != nil {
		return err
	}

	// Записываем элементы
	current = q.head
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
func (q *Queue) DeserializeFromText(r io.Reader) error {
	var count int
	_, err := fmt.Fscanf(r, "QUEUE %d", &count)
	if err != nil {
		return err
	}

	// Читаем элементы и добавляем в очередь
	q.head = nil
	q.tail = nil
	for i := 0; i < count; i++ {
		var value string
		_, err = fmt.Fscanf(r, "%s", &value)
		if err != nil {
			return err
		}
		q.Enqueue(value)
	}

	// Читаем оставшийся перевод строки
	var newline string
	fmt.Fscanf(r, "%s", &newline)

	return nil
}

// Сериализация в бинарный файл
func (q *Queue) SerializeToBinary(w io.Writer) error {
	// Записываем тип структуры (5 = QUEUE)
	binary.Write(w, binary.LittleEndian, int32(5))

	// Считаем количество элементов
	count := 0
	current := q.head
	for current != nil {
		count++
		current = current.next
	}

	binary.Write(w, binary.LittleEndian, int32(count))

	// Записываем элементы
	current = q.head
	for current != nil {
		strBytes := []byte(current.value)
		binary.Write(w, binary.LittleEndian, int32(len(strBytes)))
		binary.Write(w, binary.LittleEndian, strBytes)
		current = current.next
	}

	return nil
}

// Десериализация из бинарного файла
func (q *Queue) DeserializeFromBinary(r io.Reader) error {
	var count int32
	err := binary.Read(r, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем элементы и добавляем в очередь
	q.head = nil
	q.tail = nil
	for i := 0; i < int(count); i++ {
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

		q.Enqueue(string(strBytes))
	}

	return nil
}
