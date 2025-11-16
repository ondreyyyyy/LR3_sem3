package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var arrays = make(map[string]*DynArray)
var forwardLists = make(map[string]*ForwardList)
var doubleLists = make(map[string]*DoubleFL)
var stacks = make(map[string]*Stack)
var queues = make(map[string]*Queue)
var hashChains = make(map[string]*Hash)
var hashAddresses = make(map[string]*HashA)

func saveToFile(filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Printf("Ошибка при создании файла: %v\n", err)
		return
	}
	defer file.Close()

	writer := bufio.NewWriter(file)

	for name, arr := range arrays {
		writer.WriteString("ARRAY " + name)
		for i := 0; i < arr.size; i++ {
			elem, err := arr.GetElement(i)
			if err == nil {
				writer.WriteString(" " + elem)
			}
		}
		writer.WriteString("\n")
	}

	for name, list := range forwardLists {
		writer.WriteString("FORWARDLIST " + name)
		current := list.head
		for current != nil {
			writer.WriteString(" " + current.value)
			current = current.next
		}
		writer.WriteString("\n")
	}

	for name, list := range doubleLists {
		writer.WriteString("DOUBLELIST " + name)
		current := list.head
		for current != nil {
			writer.WriteString(" " + current.value)
			current = current.next
		}
		writer.WriteString("\n")
	}

	for name, stack := range stacks {
		writer.WriteString("STACK " + name)
		current := stack.head
		elements := []string{}
		for current != nil {
			elements = append([]string{current.value}, elements...)
			current = current.next
		}
		for _, elem := range elements {
			writer.WriteString(" " + elem)
		}
		writer.WriteString("\n")
	}

	for name, queue := range queues {
		writer.WriteString("QUEUE " + name)
		current := queue.head
		for current != nil {
			writer.WriteString(" " + current.value)
			current = current.next
		}
		writer.WriteString("\n")
	}

	// Сохранение хэш-таблиц цепочек
	for name, hash := range hashChains {
		writer.WriteString("HASHCHAIN " + name)
		for i := 0; i < hash.capacity; i++ {
			current := hash.table[i]
			for current != nil {
				writer.WriteString(" " + current.key + ":" + strconv.Itoa(current.data))
				current = current.next
			}
		}
		writer.WriteString("\n")
	}

	// Сохранение хэш-таблиц открытой адресации
	for name, hash := range hashAddresses {
		writer.WriteString("HASHADDRESS " + name)
		for i := 0; i < hash.capacity; i++ {
			if !hash.table[i].isEmpty && !hash.table[i].isDeleted {
				writer.WriteString(" " + hash.table[i].key + ":" + hash.table[i].data)
			}
		}
		writer.WriteString("\n")
	}

	writer.Flush()
}

func loadFromFile(filename string) {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Printf("Ошибка при открытии файла: %v\n", err)
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}

		tokens := strings.Fields(line)
		if len(tokens) < 2 {
			continue
		}

		typeStr := tokens[0]
		name := tokens[1]

		switch typeStr {
		case "ARRAY":
			capacity := len(tokens) - 2
			if capacity <= 0 {
				capacity = 1
			}
			arr := NewDynArray(capacity)
			for i := 2; i < len(tokens); i++ {
				arr.PushBack(tokens[i])
			}
			arrays[name] = arr

		case "FORWARDLIST":
			if len(tokens) > 2 {
				list := NewForwardList(tokens[2])
				for i := 3; i < len(tokens); i++ {
					list.AddAtTail(tokens[i])
				}
				forwardLists[name] = list
			}

		case "DOUBLELIST":
			if len(tokens) > 2 {
				list := NewDoubleFL(tokens[2])
				for i := 3; i < len(tokens); i++ {
					list.AddAtTail(tokens[i])
				}
				doubleLists[name] = list
			}

		case "STACK":
			stack := NewStack()
			for i := 2; i < len(tokens); i++ {
				stack.Push(tokens[i])
			}
			stacks[name] = stack

		case "QUEUE":
			queue := NewQueue()
			for i := 2; i < len(tokens); i++ {
				queue.Enqueue(tokens[i])
			}
			queues[name] = queue

		case "HASHCHAIN":
			hash := NewHashTable()
			for i := 2; i < len(tokens); i++ {
				parts := strings.Split(tokens[i], ":")
				if len(parts) == 2 {
					key := parts[0]
					data, err := strconv.Atoi(parts[1])
					if err == nil {
						hash.AddElement(key, data)
					}
				}
			}
			hashChains[name] = hash

		case "HASHADDRESS":
			hash := NewHashATable()
			for i := 2; i < len(tokens); i++ {
				parts := strings.Split(tokens[i], ":")
				if len(parts) == 2 {
					key := parts[0]
					data := parts[1]
					hash.AddElement(key, data)
				}
			}
			hashAddresses[name] = hash
		}
	}
}

func processHashChainCommand(args []string) {
	if len(args) < 2 {
		fmt.Println("Ошибка: недостаточно аргументов для команды", args[0])
		return
	}

	name := args[1]

	switch args[0] {
	case "HCCREATE":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для HCCREATE")
			return
		}
		if _, exists := hashChains[name]; exists {
			fmt.Printf("Ошибка: хэш-таблица цепочек '%s' уже существует\n", name)
			return
		}
		hashChains[name] = NewHashTable()
		fmt.Printf("Создание хэш-таблицы цепочек '%s' успешно\n", name)

	case "HCADD":
		if len(args) != 4 {
			fmt.Println("Ошибка: неверное количество аргументов для HCADD")
			return
		}
		hash, exists := hashChains[name]
		if !exists {
			fmt.Printf("Ошибка: хэш-таблица цепочек '%s' не существует\n", name)
			return
		}
		data, err := strconv.Atoi(args[3])
		if err != nil {
			fmt.Println("Ошибка: данные должны быть целым числом")
			return
		}
		hash.AddElement(args[2], data)
		fmt.Printf("Добавление элемента в хэш-таблицу цепочек '%s' успешно\n", name)

	case "HCFIND":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для HCFIND")
			return
		}
		hash, exists := hashChains[name]
		if !exists {
			fmt.Printf("Ошибка: хэш-таблица цепочек '%s' не существует\n", name)
			return
		}
		result := hash.FindElement(args[2])
		if result == -1 {
			fmt.Printf("Элемент '%s' не найден в хэш-таблице цепочек '%s'\n", args[2], name)
		} else {
			fmt.Printf("Элемент '%s' найден в хэш-таблице цепочек '%s': %d\n", args[2], name, result)
		}

	case "HCDELETE":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для HCDELETE")
			return
		}
		hash, exists := hashChains[name]
		if !exists {
			fmt.Printf("Ошибка: хэш-таблица цепочек '%s' не существует\n", name)
			return
		}
		hash.DeleteElement(args[2])
		fmt.Printf("Удаление элемента из хэш-таблицы цепочек '%s' успешно\n", name)
	}
}

func processHashAddressCommand(args []string) {
	if len(args) < 2 {
		fmt.Println("Ошибка: недостаточно аргументов для команды", args[0])
		return
	}

	name := args[1]

	switch args[0] {
	case "HACREATE":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для HACREATE")
			return
		}
		if _, exists := hashAddresses[name]; exists {
			fmt.Printf("Ошибка: хэш-таблица открытой адресации '%s' уже существует\n", name)
			return
		}
		hashAddresses[name] = NewHashATable()
		fmt.Printf("Создание хэш-таблицы открытой адресации '%s' успешно\n", name)

	case "HAADD":
		if len(args) != 4 {
			fmt.Println("Ошибка: неверное количество аргументов для HAADD")
			return
		}
		hash, exists := hashAddresses[name]
		if !exists {
			fmt.Printf("Ошибка: хэш-таблица открытой адресации '%s' не существует\n", name)
			return
		}
		hash.AddElement(args[2], args[3])
		fmt.Printf("Добавление элемента в хэш-таблицу открытой адресации '%s' успешно\n", name)

	case "HAFIND":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для HAFIND")
			return
		}
		hash, exists := hashAddresses[name]
		if !exists {
			fmt.Printf("Ошибка: хэш-таблица открытой адресации '%s' не существует\n", name)
			return
		}
		result := hash.FindElementStr(args[2])
		if result == "-1" {
			fmt.Printf("Элемент '%s' не найден в хэш-таблице открытой адресации '%s'\n", args[2], name)
		} else {
			fmt.Printf("Элемент '%s' найден в хэш-таблице открытой адресации '%s': %s\n", args[2], name, result)
		}

	case "HADELETE":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для HADELETE")
			return
		}
		hash, exists := hashAddresses[name]
		if !exists {
			fmt.Printf("Ошибка: хэш-таблица открытой адресации '%s' не существует\n", name)
			return
		}
		hash.DeleteElement(args[2])
		fmt.Printf("Удаление элемента из хэш-таблицы открытой адресации '%s' успешно\n", name)
	}
}

func processArrayCommand(args []string) {
	if len(args) < 2 {
		fmt.Println("Ошибка: недостаточно аргументов для команды", args[0])
		return
	}

	name := args[1]

	switch args[0] {
	case "MCREATE":
		if len(args) > 3 {
			fmt.Println("Ошибка: слишком много аргументов для MCREATE")
			return
		}
		if _, exists := arrays[name]; exists {
			fmt.Printf("Ошибка: массив '%s' уже существует\n", name)
			return
		}
		capacity := 10
		if len(args) > 2 {
			cap, err := strconv.Atoi(args[2])
			if err != nil {
				fmt.Println("Ошибка: неверная емкость массива")
				return
			}
			capacity = cap
		}
		arr := NewDynArray(capacity)
		arrays[name] = arr
		fmt.Printf("Создание массива '%s' успешно\n", name)

	case "MPUSH":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для MPUSH")
			return
		}
		arr, exists := arrays[name]
		if !exists {
			fmt.Printf("Ошибка: массив '%s' не существует\n", name)
			return
		}
		arr.PushBack(args[2])
		fmt.Printf("Добавление элемента в массив '%s' успешно\n", name)

	case "MINSERT":
		if len(args) != 4 {
			fmt.Println("Ошибка: неверное количество аргументов для MINSERT")
			return
		}
		arr, exists := arrays[name]
		if !exists {
			fmt.Printf("Ошибка: массив '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 || index > arr.size {
			fmt.Println("Ошибка: индекс вне диапазона")
			return
		}
		arr.AddAtIndex(index, args[3])
		fmt.Printf("Вставка элемента в массив '%s' успешна\n", name)

	case "MDEL":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для MDEL")
			return
		}
		arr, exists := arrays[name]
		if !exists {
			fmt.Printf("Ошибка: массив '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 || index >= arr.size {
			fmt.Println("Ошибка: индекс вне диапазона")
			return
		}
		value, err := arr.GetElement(index)
		if err != nil {
			fmt.Println("Ошибка при получении элемента:", err)
			return
		}
		arr.RemoveFromIndex(index)
		fmt.Printf("Удаление элемента '%s' из массива '%s' успешно\n", value, name)

	case "MGET":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для MGET")
			return
		}
		arr, exists := arrays[name]
		if !exists {
			fmt.Printf("Ошибка: массив '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 || index >= arr.size {
			fmt.Println("Ошибка: индекс вне диапазона")
			return
		}
		value, err := arr.GetElement(index)
		if err != nil {
			fmt.Println("Ошибка при получении элемента:", err)
			return
		}
		fmt.Printf("Элемент массива '%s' по индексу %d: %s\n", name, index, value)

	case "MSET":
		if len(args) != 4 {
			fmt.Println("Ошибка: неверное количество аргументов для MSET")
			return
		}
		arr, exists := arrays[name]
		if !exists {
			fmt.Printf("Ошибка: массив '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 || index >= arr.size {
			fmt.Println("Ошибка: индекс вне диапазона")
			return
		}
		arr.ReplaceElement(index, args[3])
		fmt.Printf("Замена элемента в массиве '%s' успешна\n", name)

	case "MSIZE", "MLENGTH":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для", args[0])
			return
		}
		arr, exists := arrays[name]
		if !exists {
			fmt.Printf("Ошибка: массив '%s' не существует\n", name)
			return
		}
		size := arr.Length()
		fmt.Printf("Размер массива '%s': %d\n", name, size)
	}
}

func processStackCommand(args []string) {
	if len(args) < 2 {
		fmt.Println("Ошибка: недостаточно аргументов для команды", args[0])
		return
	}

	name := args[1]

	switch args[0] {
	case "SCREATE":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для SCREATE")
			return
		}
		if _, exists := stacks[name]; exists {
			fmt.Printf("Ошибка: стек '%s' уже существует\n", name)
			return
		}
		stacks[name] = NewStack()
		fmt.Printf("Создание стека '%s' успешно\n", name)

	case "SPUSH":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для SPUSH")
			return
		}
		stack, exists := stacks[name]
		if !exists {
			fmt.Printf("Ошибка: стек '%s' не существует\n", name)
			return
		}
		stack.Push(args[2])
		fmt.Printf("Добавление элемента в стек '%s' успешно\n", name)

	case "SPOP":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для SPOP")
			return
		}
		stack, exists := stacks[name]
		if !exists {
			fmt.Printf("Ошибка: стек '%s' не существует\n", name)
			return
		}
		if stack.head == nil {
			fmt.Println("Ошибка: стек пуст")
			return
		}
		value, err := stack.Pop()
		if err != nil {
			fmt.Println("Ошибка при извлечении из стека:", err)
			return
		}
		fmt.Printf("Удаление элемента из стека '%s' успешно. Удаленный элемент: %s\n", name, value)
	}
}

func processQueueCommand(args []string) {
	if len(args) < 2 {
		fmt.Println("Ошибка: недостаточно аргументов для команды", args[0])
		return
	}

	name := args[1]

	switch args[0] {
	case "QCREATE":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для QCREATE")
			return
		}
		if _, exists := queues[name]; exists {
			fmt.Printf("Ошибка: очередь '%s' уже существует\n", name)
			return
		}
		queues[name] = NewQueue()
		fmt.Printf("Создание очереди '%s' успешно\n", name)

	case "QPUSH":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для QPUSH")
			return
		}
		queue, exists := queues[name]
		if !exists {
			fmt.Printf("Ошибка: очередь '%s' не существует\n", name)
			return
		}
		queue.Enqueue(args[2])
		fmt.Printf("Добавление элемента в очередь '%s' успешно\n", name)

	case "QPOP":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для QPOP")
			return
		}
		queue, exists := queues[name]
		if !exists {
			fmt.Printf("Ошибка: очередь '%s' не существует\n", name)
			return
		}
		if queue.head == nil {
			fmt.Println("Ошибка: очередь пуста")
			return
		}
		value := queue.head.value
		queue.Dequeue()
		fmt.Printf("Удаление элемента из очереди '%s' успешно. Удаленный элемент: %s\n", name, value)
	}
}

func processForwardListCommand(args []string) {
	if len(args) < 2 {
		fmt.Println("Ошибка: недостаточно аргументов для команды", args[0])
		return
	}

	name := args[1]

	switch args[0] {
	case "FCREATE":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для FCREATE")
			return
		}
		if _, exists := forwardLists[name]; exists {
			fmt.Printf("Ошибка: список '%s' уже существует\n", name)
			return
		}
		list := NewForwardList(args[2])
		forwardLists[name] = list
		fmt.Printf("Создание односвязного списка '%s' успешно\n", name)

	case "FPUSHHEAD":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для FPUSHHEAD")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		list.AddAtHead(args[2])
		fmt.Printf("Добавление элемента в голову списка '%s' успешно\n", name)

	case "FPUSHTAIL":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для FPUSHTAIL")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		list.AddAtTail(args[2])
		fmt.Printf("Добавление элемента в хвост списка '%s' успешно\n", name)

	case "FINSERTBEFORE":
		if len(args) != 4 {
			fmt.Println("Ошибка: неверное количество аргументов для FINSERTBEFORE")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 {
			fmt.Println("Ошибка: индекс не может быть отрицательным")
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		list.AddBeforeIndex(args[3], index)
		fmt.Printf("Вставка элемента перед индексом %d списка '%s' успешна\n", index, name)

	case "FINSERTAFTER":
		if len(args) != 4 {
			fmt.Println("Ошибка: неверное количество аргументов для FINSERTAFTER")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 {
			fmt.Println("Ошибка: индекс не может быть отрицательным")
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		list.AddAfterIndex(args[3], index)
		fmt.Printf("Вставка элемента после индекса %d списка '%s' успешна\n", index, name)

	case "FDELHEAD":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для FDELHEAD")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		value := list.head.value
		list.DeleteAtHead()
		fmt.Printf("Удаление головы списка '%s' успешно. Удаленный элемент: %s\n", name, value)

	case "FDELTAIL":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для FDELTAIL")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		value := list.tail.value
		list.DeleteAtTail()
		fmt.Printf("Удаление хвоста списка '%s' успешно. Удаленный элемент: %s\n", name, value)

	case "FDELBEFORE":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для FDELBEFORE")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 {
			fmt.Println("Ошибка: индекс не может быть отрицательным")
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		if index == 0 {
			fmt.Println("Ошибка: невозможно удалить элемент перед первым элементом")
			return
		}
		list.DeleteBeforeIndex(index)
		fmt.Printf("Удаление элемента перед индексом %d списка '%s' успешно\n", index, name)

	case "FDELAFTER":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для FDELAFTER")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 {
			fmt.Println("Ошибка: индекс не может быть отрицательным")
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		list.DeleteAfterIndex(index)
		fmt.Printf("Удаление элемента после индекса %d списка '%s' успешно\n", index, name)

	case "FDELVALUE":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для FDELVALUE")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		list.DeleteValue(args[2])
		fmt.Printf("Удаление элемента '%s' из списка '%s' успешно\n", args[2], name)

	case "FSEARCH":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для FSEARCH")
			return
		}
		list, exists := forwardLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		list.SearchNode(args[2])
	}
}

func processDoubleListCommand(args []string) {
	if len(args) < 2 {
		fmt.Println("Ошибка: недостаточно аргументов для команды", args[0])
		return
	}

	name := args[1]

	switch args[0] {
	case "LCREATE":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для LCREATE")
			return
		}
		if _, exists := doubleLists[name]; exists {
			fmt.Printf("Ошибка: список '%s' уже существует\n", name)
			return
		}
		list := NewDoubleFL(args[2])
		doubleLists[name] = list
		fmt.Printf("Создание двусвязного списка '%s' успешно\n", name)

	case "LPUSHHEAD":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для LPUSHHEAD")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		list.AddAtHead(args[2])
		fmt.Printf("Добавление элемента в голову списка '%s' успешно\n", name)

	case "LPUSHTAIL":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для LPUSHTAIL")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		list.AddAtTail(args[2])
		fmt.Printf("Добавление элемента в хвост списка '%s' успешно\n", name)

	case "LINSERTBEFORE":
		if len(args) != 4 {
			fmt.Println("Ошибка: неверное количество аргументов для LINSERTBEFORE")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 {
			fmt.Println("Ошибка: индекс не может быть отрицательным")
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		list.AddBeforeIndex(args[3], index)
		fmt.Printf("Вставка элемента перед индексом %d списка '%s' успешна\n", index, name)

	case "LINSERTAFTER":
		if len(args) != 4 {
			fmt.Println("Ошибка: неверное количество аргументов для LINSERTAFTER")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 {
			fmt.Println("Ошибка: индекс не может быть отрицательным")
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		list.AddAfterIndex(args[3], index)
		fmt.Printf("Вставка элемента после индекса %d списка '%s' успешна\n", index, name)

	case "LDELHEAD":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для LDELHEAD")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		value := list.head.value
		list.DeleteAtHead()
		fmt.Printf("Удаление головы списка '%s' успешно. Удаленный элемент: %s\n", name, value)

	case "LDELTAIL":
		if len(args) != 2 {
			fmt.Println("Ошибка: неверное количество аргументов для LDELTAIL")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		value := list.tail.value
		list.DeleteAtTail()
		fmt.Printf("Удаление хвоста списка '%s' успешно. Удаленный элемент: %s\n", name, value)

	case "LDELBEFORE":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для LDELBEFORE")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 {
			fmt.Println("Ошибка: индекс не может быть отрицательным")
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		if index == 0 {
			fmt.Println("Ошибка: невозможно удалить элемент перед первым элементом")
			return
		}
		list.DeleteBeforeIndex(index)
		fmt.Printf("Удаление элемента перед индексом %d списка '%s' успешно\n", index, name)

	case "LDELAFTER":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для LDELAFTER")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		index, err := strconv.Atoi(args[2])
		if err != nil || index < 0 {
			fmt.Println("Ошибка: индекс не может быть отрицательным")
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		list.DeleteAfterIndex(index)
		fmt.Printf("Удаление элемента после индекса %d списка '%s' успешно\n", index, name)

	case "LDELVALUE":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для LDELVALUE")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		if list.head == nil {
			fmt.Println("Ошибка: список пуст")
			return
		}
		list.DeleteValue(args[2])
		fmt.Printf("Удаление элемента '%s' из списка '%s' успешно\n", args[2], name)

	case "LSEARCH":
		if len(args) != 3 {
			fmt.Println("Ошибка: неверное количество аргументов для LSEARCH")
			return
		}
		list, exists := doubleLists[name]
		if !exists {
			fmt.Printf("Ошибка: список '%s' не существует\n", name)
			return
		}
		list.SearchValue(args[2])
	}
}

func processPrintCommand(args []string) {
	if len(args) != 2 {
		fmt.Println("Ошибка: неверное количество аргументов для PRINT. Ожидается: PRINT <name>")
		return
	}

	name := args[1]

	if arr, exists := arrays[name]; exists {
		fmt.Printf("Содержимое массива '%s': ", name)
		arr.Print()
	} else if list, exists := forwardLists[name]; exists {
		fmt.Printf("Содержимое односвязного списка '%s': ", name)
		list.Print()
	} else if list, exists := doubleLists[name]; exists {
		fmt.Printf("Содержимое двусвязного списка '%s': ", name)
		list.Print()
	} else if stack, exists := stacks[name]; exists {
		fmt.Printf("Содержимое стека '%s': ", name)
		stack.Print()
	} else if queue, exists := queues[name]; exists {
		fmt.Printf("Содержимое очереди '%s': ", name)
		queue.Print()
	} else if hash, exists := hashChains[name]; exists {
		fmt.Printf("Содержимое хэш-таблицы цепочек '%s':\n", name)
		hash.PrintHashTable()
	} else if hash, exists := hashAddresses[name]; exists {
		fmt.Printf("Содержимое хэш-таблицы открытой адресации '%s':\n", name)
		hash.PrintHashTable()
	} else {
		fmt.Printf("Ошибка: структура данных с именем '%s' не найдена\n", name)
	}
}

func printHelp() {
	fmt.Println("=== СПРАВКА ПО КОМАНДАМ ===")
	fmt.Println("\nМАССИВЫ:")
	fmt.Println("  MCREATE <name> [capacity] - Создать массив")
	fmt.Println("  MPUSH <name> <value>      - Добавить элемент")
	fmt.Println("  MINSERT <name> <index> <value> - Вставить элемент")
	fmt.Println("  MDEL <name> <index>       - Удалить элемент")
	fmt.Println("  MGET <name> <index>       - Получить элемент")
	fmt.Println("  MSET <name> <index> <value> - Заменить элемент")
	fmt.Println("  MSIZE <name>              - Размер массива")

	fmt.Println("\nОДНОСВЯЗНЫЕ СПИСКИ:")
	fmt.Println("  FCREATE <name> <value>    - Создать список")
	fmt.Println("  FPUSHHEAD <name> <value>  - Добавить в голову")
	fmt.Println("  FPUSHTAIL <name> <value>  - Добавить в хвост")
	fmt.Println("  FINSERTBEFORE <name> <index> <value> - Добавить перед индексом")
	fmt.Println("  FINSERTAFTER <name> <index> <value> - Добавить после индекса")
	fmt.Println("  FDELHEAD <name>           - Удалить голову")
	fmt.Println("  FDELTAIL <name>           - Удалить хвост")
	fmt.Println("  FDELBEFORE <name> <index> - Удалить перед индексом")
	fmt.Println("  FDELAFTER <name> <index>  - Удалить после индекса")
	fmt.Println("  FDELVALUE <name> <value>  - Удалить по значению")
	fmt.Println("  FSEARCH <name> <value>    - Найти элемент")

	fmt.Println("\nДВУСВЯЗНЫЕ СПИСКИ:")
	fmt.Println("  LCREATE <name> <value>    - Создать список")
	fmt.Println("  LPUSHHEAD <name> <value>  - Добавить в голову")
	fmt.Println("  LPUSHTAIL <name> <value>  - Добавить в хвост")
	fmt.Println("  LINSERTBEFORE <name> <index> <value> - Добавить перед индексом")
	fmt.Println("  LINSERTAFTER <name> <index> <value> - Добавить после индекса")
	fmt.Println("  LDELHEAD <name>           - Удалить голову")
	fmt.Println("  LDELTAIL <name>           - Удалить хвост")
	fmt.Println("  LDELBEFORE <name> <index> - Удалить перед индексом")
	fmt.Println("  LDELAFTER <name> <index>  - Удалить после индекса")
	fmt.Println("  LDELVALUE <name> <value>  - Удалить по значению")
	fmt.Println("  LSEARCH <name> <value>    - Найти элемент")

	fmt.Println("\nСТЕКИ:")
	fmt.Println("  SCREATE <name>            - Создать стек")
	fmt.Println("  SPUSH <name> <value>      - Добавить элемент")
	fmt.Println("  SPOP <name>               - Удалить элемент")

	fmt.Println("\nОЧЕРЕДИ:")
	fmt.Println("  QCREATE <name>            - Создать очередь")
	fmt.Println("  QPUSH <name> <value>      - Добавить элемент")
	fmt.Println("  QPOP <name>               - Удалить элемент")

	fmt.Println("\nХЭШ-ТАБЛИЦЫ ЦЕПОЧЕК:")
	fmt.Println("  HCCREATE <name>           - Создать хэш-таблицу цепочек")
	fmt.Println("  HCADD <name> <key> <value> - Добавить элемент")
	fmt.Println("  HCFIND <name> <key>        - Найти элемент")
	fmt.Println("  HCDELETE <name> <key>      - Удалить элемент")

	fmt.Println("\nХЭШ-ТАБЛИЦЫ ОТКРЫТОЙ АДРЕСАЦИИ:")
	fmt.Println("  HACREATE <name>           - Создать хэш-таблицу открытой адресации")
	fmt.Println("  HAADD <name> <key> <value> - Добавить элемент")
	fmt.Println("  HAFIND <name> <key>        - Найти элемент")
	fmt.Println("  HADELETE <name> <key>      - Удалить элемент")

	fmt.Println("\nОБЩИЕ КОМАНДЫ:")
	fmt.Println("  PRINT <name>              - Показать содержимое структуры")
	fmt.Println("  HELP                      - Справка")

	fmt.Println("\nПРИМЕРЫ ЗАПУСКА:")
	fmt.Println("  ./dbms --file data.txt --query 'MCREATE myarr'")
	fmt.Println("  ./dbms --file data.txt --query 'MPUSH myarr value'")
	fmt.Println("  ./dbms --file data.txt --query 'PRINT myarr'")
	fmt.Println("  ./dbms --help")
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Ошибка: неверное количество аргументов. Используйте --help для справки.")
		os.Exit(1)
	}

	var filename, query string

	for i := 1; i < len(os.Args); i++ {
		arg := os.Args[i]
		if arg == "--file" && i+1 < len(os.Args) {
			filename = os.Args[i+1]
			i++
		} else if arg == "--query" && i+1 < len(os.Args) {
			query = os.Args[i+1]
			i++
		} else if arg == "--help" || arg == "-h" {
			printHelp()
			return
		} else {
			fmt.Printf("Ошибка: неизвестный аргумент %s\n", arg)
			os.Exit(1)
		}
	}

	if filename == "" || query == "" {
		fmt.Println("Ошибка: необходимо указать --file и --query")
		os.Exit(1)
	}

	loadFromFile(filename)

	args := strings.Fields(query)
	if len(args) == 0 {
		fmt.Println("Ошибка: пустой запрос")
		os.Exit(1)
	}

	command := args[0]

	switch command {
	case "MCREATE", "MPUSH", "MINSERT", "MDEL", "MGET", "MSET", "MSIZE", "MLENGTH":
		processArrayCommand(args)
	case "FCREATE", "FPUSHHEAD", "FPUSHTAIL", "FINSERTBEFORE", "FINSERTAFTER",
		"FDELHEAD", "FDELTAIL", "FDELBEFORE", "FDELAFTER", "FDELVALUE", "FSEARCH":
		processForwardListCommand(args)
	case "LCREATE", "LPUSHHEAD", "LPUSHTAIL", "LINSERTBEFORE", "LINSERTAFTER",
		"LDELHEAD", "LDELTAIL", "LDELBEFORE", "LDELAFTER", "LDELVALUE", "LSEARCH":
		processDoubleListCommand(args)
	case "SCREATE", "SPUSH", "SPOP":
		processStackCommand(args)
	case "QCREATE", "QPUSH", "QPOP":
		processQueueCommand(args)
	case "HCCREATE", "HCADD", "HCFIND", "HCDELETE":
		processHashChainCommand(args)
	case "HACREATE", "HAADD", "HAFIND", "HADELETE":
		processHashAddressCommand(args)
	case "PRINT":
		processPrintCommand(args)
	case "HELP":
		printHelp()
	default:
		fmt.Printf("Ошибка: неизвестная команда '%s'\n", command)
		fmt.Println("Используйте HELP для просмотра доступных команд.")
		os.Exit(1)
	}
	saveToFile(filename)
}
