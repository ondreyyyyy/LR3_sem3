package main

import (
	"encoding/binary"
	"errors"
	"fmt"
	"io"
)

type StackNode struct {
	value string
	next  *StackNode
}

type Stack struct {
	head *StackNode
}

func NewStack() *Stack {
	return &Stack{
		head: nil,
	}
}

func (s *Stack) Destroy() {
	for s.head != nil {
		s.head = s.head.next
	}
}

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

func (s *Stack) SerializeToText(w io.Writer) error {
	// Собираем элементы стека в правильном порядке
	var values []string
	current := s.head
	for current != nil {
		values = append([]string{current.value}, values...)
		current = current.next
	}

	_, err := fmt.Fprintf(w, "STACK %d", len(values))
	if err != nil {
		return err
	}

	for _, value := range values {
		_, err = fmt.Fprintf(w, " %s", value)
		if err != nil {
			return err
		}
	}
	_, err = fmt.Fprintln(w)
	return err
}

// Десериализация из текстового файла
func (s *Stack) DeserializeFromText(r io.Reader) error {
	var count int
	_, err := fmt.Fscanf(r, "STACK %d", &count)
	if err != nil {
		return err
	}

	// Читаем элементы
	values := make([]string, count)
	for i := 0; i < count; i++ {
		_, err = fmt.Fscanf(r, "%s", &values[i])
		if err != nil {
			return err
		}
	}

	// Восстанавливаем стек
	s.head = nil
	for i := count - 1; i >= 0; i-- {
		s.Push(values[i])
	}

	// Читаем оставшийся перевод строки
	var newline string
	fmt.Fscanf(r, "%s", &newline)

	return nil
}

// Сериализация в бинарный файл
func (s *Stack) SerializeToBinary(w io.Writer) error {
	// Записываем тип структуры (4 = STACK)
	binary.Write(w, binary.LittleEndian, int32(4))

	// Собираем элементы стека в правильном порядке
	var values []string
	current := s.head
	for current != nil {
		values = append([]string{current.value}, values...)
		current = current.next
	}

	count := len(values)
	binary.Write(w, binary.LittleEndian, int32(count))

	// Записываем элементы
	for _, value := range values {
		strBytes := []byte(value)
		binary.Write(w, binary.LittleEndian, int32(len(strBytes)))
		binary.Write(w, binary.LittleEndian, strBytes)
	}

	return nil
}

// Десериализация из бинарного файла
func (s *Stack) DeserializeFromBinary(r io.Reader) error {
	var count int32
	err := binary.Read(r, binary.LittleEndian, &count)
	if err != nil {
		return err
	}

	// Читаем элементы
	values := make([]string, count)
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

		values[i] = string(strBytes)
	}

	// Восстанавливаем стек
	s.head = nil
	for i := int(count) - 1; i >= 0; i-- {
		s.Push(values[i])
	}

	return nil
}
