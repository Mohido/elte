import { Component, OnInit, Input, Output, EventEmitter } from '@angular/core';
import { Todo } from '../../classes/todo';

@Component({
  selector: 'app-todo',
  templateUrl: './todo.component.html',
  styleUrls: ['./todo.component.css']
})
export class TodoComponent implements OnInit {
  @Input()
  public todo: Todo;

  @Output()
  public delTodo: EventEmitter<number> = new EventEmitter();

  public clickButton(): void {
    this.delTodo.emit(this.todo.id);
  }

  constructor() { }

  ngOnInit() {
  }

}