package main

import (
	"errors"
	"fmt"
)

type StackNode struct {
	value string
	next  *StackNode
}

type Stack struct {
	head *StackNode
}

// Конструктор
func NewStack() *Stack {
	return &Stack{
		head: nil,
	}
}

// Деструктор
func (s *Stack) Destroy() {
	for s.head != nil {
		s.head = s.head.next
	}
}

// Методы стека
func (s *Stack) Push(value string) {
	newNode := &StackNode{
		value: value,
		next:  s.head,
	}
	s.head = newNode
}

func (s *Stack) Pop() (string, error) {
	if s.head == nil {
		return "", errors.New("error")
	}

	futureDelete := s.head
	value := futureDelete.value
	s.head = s.head.next
	return value, nil
}

func (s *Stack) GetElement(index int) (string, error) {
	if index < 0 {
		return "", errors.New("error")
	}

	current := s.head
	for i := 0; i < index; i++ {
		if current == nil {
			return "", errors.New("error")
		}
		current = current.next
	}

	if current == nil {
		return "", errors.New("error")
	}
	return current.value, nil
}

func (s *Stack) Print() {
	if s.head == nil {
		fmt.Println("Стек пуст.")
		return
	}

	fmt.Print("Стек: ")
	curElem := s.head
	for curElem != nil {
		fmt.Print(curElem.value + " ")
		curElem = curElem.next
	}
	fmt.Println()
}

// Геттер для проверки пустоты
func (s *Stack) IsEmpty() bool {
	return s.head == nil
}
