package main

import (
	"strconv"
	"testing"
)

func BenchmarkForwardList_AddAtHead(b *testing.B) {
	list := &ForwardList{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.AddAtHead("element" + strconv.Itoa(i))
	}
}

func BenchmarkForwardList_AddAtTail(b *testing.B) {
	list := &ForwardList{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
}

func BenchmarkForwardList_SearchNode(b *testing.B) {
	list := NewForwardList("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.SearchNode("element500")
	}
}

func BenchmarkForwardList_AddBeforeIndex(b *testing.B) {
	list := NewForwardList("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.AddBeforeIndex("new", 500)
	}
}

func BenchmarkForwardList_AddAfterIndex(b *testing.B) {
	list := NewForwardList("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.AddAfterIndex("new", 500)
	}
}

func BenchmarkForwardList_DeleteAtHead(b *testing.B) {
	list := NewForwardList("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if list.head != nil {
			list.DeleteAtHead()
		}
	}
}

func BenchmarkForwardList_DeleteAtTail(b *testing.B) {
	list := NewForwardList("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if list.head != nil {
			list.DeleteAtTail()
		}
	}
}

func BenchmarkForwardList_DeleteValue(b *testing.B) {
	list := NewForwardList("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.DeleteValue("element500")
	}
}

func BenchmarkDoubleFL_AddAtHead(b *testing.B) {
	list := &DoubleFL{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.AddAtHead("element" + strconv.Itoa(i))
	}
}

func BenchmarkDoubleFL_AddAtTail(b *testing.B) {
	list := &DoubleFL{}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
}

func BenchmarkDoubleFL_AddBeforeIndex(b *testing.B) {
	list := NewDoubleFL("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.AddBeforeIndex("new", 500)
	}
}

func BenchmarkDoubleFL_AddAfterIndex(b *testing.B) {
	list := NewDoubleFL("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.AddAfterIndex("new", 500)
	}
}

func BenchmarkDoubleFL_DeleteAtHead(b *testing.B) {
	list := NewDoubleFL("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if list.head != nil {
			list.DeleteAtHead()
		}
	}
}

func BenchmarkDoubleFL_DeleteAtTail(b *testing.B) {
	list := NewDoubleFL("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if list.head != nil {
			list.DeleteAtTail()
		}
	}
}

func BenchmarkDoubleFL_DeleteValue(b *testing.B) {
	list := NewDoubleFL("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.DeleteValue("element500")
	}
}

func BenchmarkDoubleFL_SearchValue(b *testing.B) {
	list := NewDoubleFL("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.SearchValue("element500")
	}
}

func BenchmarkDynArray_AddAtIndex(b *testing.B) {
	arr := NewDynArray(10)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.AddAtIndex(0, "element"+strconv.Itoa(i))
	}
}

func BenchmarkDynArray_PushBack(b *testing.B) {
	arr := NewDynArray(10)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.PushBack("element" + strconv.Itoa(i))
	}
}

func BenchmarkDynArray_GetElement(b *testing.B) {
	arr := NewDynArray(1000)
	for i := 0; i < 1000; i++ {
		arr.PushBack("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.GetElement(500)
	}
}

func BenchmarkDynArray_RemoveFromIndex(b *testing.B) {
	arr := NewDynArray(1000)
	for i := 0; i < 1000; i++ {
		arr.PushBack("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if arr.size > 0 {
			arr.RemoveFromIndex(0)
		}
	}
}

func BenchmarkDynArray_ReplaceElement(b *testing.B) {
	arr := NewDynArray(1000)
	for i := 0; i < 1000; i++ {
		arr.PushBack("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.ReplaceElement(500, "new")
	}
}

// Benchmark tests for Queue
func BenchmarkQueue_Enqueue(b *testing.B) {
	queue := NewQueue()
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		queue.Enqueue("element" + strconv.Itoa(i))
	}
}

func BenchmarkQueue_Dequeue(b *testing.B) {
	queue := NewQueue()
	for i := 0; i < 1000; i++ {
		queue.Enqueue("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if queue.head != nil {
			queue.Dequeue()
		}
	}
}

func BenchmarkStack_Push(b *testing.B) {
	stack := NewStack()
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		stack.Push("element" + strconv.Itoa(i))
	}
}

func BenchmarkStack_Pop(b *testing.B) {
	stack := NewStack()
	for i := 0; i < 1000; i++ {
		stack.Push("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		if stack.head != nil {
			stack.Pop()
		}
	}
}

func BenchmarkHash_AddElement(b *testing.B) {
	hash := NewHashTable()
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hash.AddElement("key"+strconv.Itoa(i), i)
	}
}

func BenchmarkHash_FindElement(b *testing.B) {
	hash := NewHashTable()
	for i := 0; i < 1000; i++ {
		hash.AddElement("key"+strconv.Itoa(i), i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hash.FindElement("key500")
	}
}

func BenchmarkHash_DeleteElement(b *testing.B) {
	hash := NewHashTable()
	for i := 0; i < 1000; i++ {
		hash.AddElement("key"+strconv.Itoa(i), i)
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hash.DeleteElement("key500")
	}
}

func BenchmarkHashA_AddElement(b *testing.B) {
	hash := NewHashATable()
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hash.AddElement("key"+strconv.Itoa(i), "value"+strconv.Itoa(i))
	}
}

func BenchmarkHashA_FindElement(b *testing.B) {
	hash := NewHashATable()
	for i := 0; i < 1000; i++ {
		hash.AddElement("key"+strconv.Itoa(i), "value"+strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hash.FindElement("key500")
	}
}

func BenchmarkHashA_FindElementStr(b *testing.B) {
	hash := NewHashATable()
	for i := 0; i < 1000; i++ {
		hash.AddElement("key"+strconv.Itoa(i), "value"+strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hash.FindElementStr("key500")
	}
}

func BenchmarkHashA_DeleteElement(b *testing.B) {
	hash := NewHashATable()
	for i := 0; i < 1000; i++ {
		hash.AddElement("key"+strconv.Itoa(i), "value"+strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hash.DeleteElement("key500")
	}
}

func BenchmarkDynArray_Resize(b *testing.B) {
	arr := NewDynArray(2)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		arr.PushBack("element" + strconv.Itoa(i))
	}
}

func BenchmarkHashA_Rehash(b *testing.B) {
	hash := NewHashATable()
	for i := 0; i < 7; i++ {
		hash.AddElement("key"+strconv.Itoa(i), "value"+strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		hash.AddElement("trigger", "rehash")
	}
}

// Benchmark tests for edge cases
func BenchmarkForwardList_DeleteBeforeIndex(b *testing.B) {
	list := NewForwardList("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.DeleteBeforeIndex(500)
	}
}

func BenchmarkForwardList_DeleteAfterIndex(b *testing.B) {
	list := NewForwardList("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.DeleteAfterIndex(500)
	}
}

func BenchmarkDoubleFL_DeleteBeforeIndex(b *testing.B) {
	list := NewDoubleFL("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.DeleteBeforeIndex(500)
	}
}

func BenchmarkDoubleFL_DeleteAfterIndex(b *testing.B) {
	list := NewDoubleFL("start")
	for i := 0; i < 1000; i++ {
		list.AddAtTail("element" + strconv.Itoa(i))
	}
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		list.DeleteAfterIndex(500)
	}
}
