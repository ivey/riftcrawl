package main

import (
	"fmt"

	"github.com/nsf/termbox-go"
	"github.com/davecgh/go-spew/spew"
)

func write(text string) {
	j := 0
	for _, r := range text {
		termbox.SetCell(j, 8, r, termbox.ColorDefault, termbox.ColorDefault)
		j += 1
	}
}

func main() {
	fmt.Printf("riftcrawl\n")

	err := termbox.Init()
	if err != nil {
		panic(err)
	}
	defer termbox.Close()

	termbox.Clear(termbox.ColorDefault, termbox.ColorDefault)
	termbox.SetCursor(0,0)
	fmt.Printf("riftcrawl - Enter character, ESC to quit")

loop:
	for {
		switch ev := termbox.PollEvent(); ev.Type {
		case termbox.EventKey:
			if ev.Key == termbox.KeyEsc {
				break loop
			}
			write(spew.Sprintf("%v", ev))
			termbox.Flush()
		}
	}
}
