package main

import (
	"encoding/binary"
	"fmt"
	"io"
	"os"
)

func main() {
	fmt.Println("=== Тестирование сериализации и десериализации в единые файлы ===")

	// Создаем тестовые структуры
	structures := createTestStructures()

	// Сериализация в текстовый файл
	err := serializeAllToText(structures, "output.txt")
	if err != nil {
		fmt.Printf("Ошибка сериализации в текст: %v\n", err)
	} else {
		fmt.Println("Сериализация в output.txt успешна")
	}

	// Сериализация в бинарный файл
	err = serializeAllToBinary(structures, "output.bin")
	if err != nil {
		fmt.Printf("Ошибка сериализации в бинарный файл: %v\n", err)
	} else {
		fmt.Println("Сериализация в output.bin успешна")
	}

	// Десериализация из текстового файла
	fmt.Println("\n--- Десериализация из output.txt ---")
	textStructures, err := deserializeAllFromText("output.txt")
	if err != nil {
		fmt.Printf("Ошибка десериализации из текста: %v\n", err)
	} else {
		printAllStructures(textStructures, "Текстовая десериализация")
	}

	// Десериализация из бинарного файла
	fmt.Println("\n--- Десериализация из output.bin ---")
	binaryStructures, err := deserializeAllFromBinary("output.bin")
	if err != nil {
		fmt.Printf("Ошибка десериализации из бинарного файла: %v\n", err)
	} else {
		printAllStructures(binaryStructures, "Бинарная десериализация")
	}

	fmt.Println("=== Все тесты завершены ===")
}

// Структура для хранения всех тестовых структур
type AllStructures struct {
	array       *DynArray
	forwardList *ForwardList
	doubleList  *DoubleFL
	stack       *Stack
	queue       *Queue
	hashA       *HashA
	hash        *Hash
}

func createTestStructures() *AllStructures {
	// DynArray
	arr := NewDynArray(5)
	arr.PushBack("one")
	arr.PushBack("two")
	arr.PushBack("three")

	// ForwardList
	fl := NewForwardList("first")
	fl.AddAtTail("second")
	fl.AddAtTail("third")

	// DoubleFL
	dfl := NewDoubleFL("first")
	dfl.AddAtTail("second")
	dfl.AddAtTail("third")

	// Stack
	stack := NewStack()
	stack.Push("first")
	stack.Push("second")
	stack.Push("third")

	// Queue
	queue := NewQueue()
	queue.Enqueue("first")
	queue.Enqueue("second")
	queue.Enqueue("third")

	// HashA
	hashA := NewHashATable()
	hashA.AddElement("key1", "100")
	hashA.AddElement("key2", "200")

	// Hash
	hash := NewHashTable()
	hash.AddElement("key1", 100)
	hash.AddElement("key2", 200)

	return &AllStructures{
		array:       arr,
		forwardList: fl,
		doubleList:  dfl,
		stack:       stack,
		queue:       queue,
		hashA:       hashA,
		hash:        hash,
	}
}

func serializeAllToText(structures *AllStructures, filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Сериализуем все структуры последовательно
	structures.array.SerializeToText(file)
	structures.forwardList.SerializeToText(file)
	structures.doubleList.SerializeToText(file)
	structures.stack.SerializeToText(file)
	structures.queue.SerializeToText(file)
	structures.hashA.SerializeToText(file)
	structures.hash.SerializeToText(file)

	return nil
}

func serializeAllToBinary(structures *AllStructures, filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	// Сериализуем все структуры последовательно
	structures.array.SerializeToBinary(file)
	structures.forwardList.SerializeToBinary(file)
	structures.doubleList.SerializeToBinary(file)
	structures.stack.SerializeToBinary(file)
	structures.queue.SerializeToBinary(file)
	structures.hashA.SerializeToBinary(file)
	structures.hash.SerializeToBinary(file)

	return nil
}

func deserializeAllFromText(filename string) (*AllStructures, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	structures := &AllStructures{
		array:       NewDynArray(1),
		forwardList: &ForwardList{},
		doubleList:  &DoubleFL{},
		stack:       NewStack(),
		queue:       NewQueue(),
		hashA:       NewHashATable(),
		hash:        NewHashTable(),
	}

	// Десериализуем все структуры в том же порядке
	structures.array.DeserializeFromText(file)
	structures.forwardList.DeserializeFromText(file)
	structures.doubleList.DeserializeFromText(file)
	structures.stack.DeserializeFromText(file)
	structures.queue.DeserializeFromText(file)
	structures.hashA.DeserializeFromText(file)
	structures.hash.DeserializeFromText(file)

	return structures, nil
}

func deserializeAllFromBinary(filename string) (*AllStructures, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	structures := &AllStructures{
		array:       NewDynArray(1),
		forwardList: &ForwardList{},
		doubleList:  &DoubleFL{},
		stack:       NewStack(),
		queue:       NewQueue(),
		hashA:       NewHashATable(),
		hash:        NewHashTable(),
	}

	// Читаем и десериализуем структуры по типу
	for {
		var structType int32
		err := binary.Read(file, binary.LittleEndian, &structType)
		if err == io.EOF {
			break
		}
		if err != nil {
			return nil, err
		}

		switch structType {
		case 1: // ARRAY
			structures.array.DeserializeFromBinary(file)
		case 2: // FORWARDLIST
			structures.forwardList.DeserializeFromBinary(file)
		case 3: // DOUBLELIST
			structures.doubleList.DeserializeFromBinary(file)
		case 4: // STACK
			structures.stack.DeserializeFromBinary(file)
		case 5: // QUEUE
			structures.queue.DeserializeFromBinary(file)
		case 6: // HASHA
			structures.hashA.DeserializeFromBinary(file)
		case 7: // HASH
			structures.hash.DeserializeFromBinary(file)
		default:
			return nil, fmt.Errorf("неизвестный тип структуры: %d", structType)
		}
	}

	return structures, nil
}

func printAllStructures(structures *AllStructures, title string) {
	fmt.Printf("\n--- %s ---\n", title)
	fmt.Print("Массив: ")
	structures.array.Print()
	fmt.Print("Односвязный список: ")
	structures.forwardList.Print()
	fmt.Print("Двусвязный список: ")
	structures.doubleList.Print()
	fmt.Print("Стек: ")
	structures.stack.Print()
	fmt.Print("Очередь: ")
	structures.queue.Print()
	fmt.Println("Хэш-таблица (адресация):")
	structures.hashA.PrintHashTable()
	fmt.Println("Хэш-таблица (цепочки):")
	structures.hash.PrintHashTable()
}
