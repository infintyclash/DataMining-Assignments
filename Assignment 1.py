import json
import os
import time
from datetime import datetime
from plyer import notification

TODO_FILE = "tasks.json"

# Load tasks
def load_tasks():
    if os.path.exists(TODO_FILE):
        with open(TODO_FILE, "r") as file:
            return json.load(file)
    return []

# Save tasks
def save_tasks(tasks):
    with open(TODO_FILE, "w") as file:
        json.dump(tasks, file, indent=2)

# Add task
def add_task():
    task = input("Enter your task: ")
    alarm_time = input("Enter reminder time (HH:MM, 24-hour format): ")
    tasks.append({"task": task, "done": False, "time": alarm_time})
    save_tasks(tasks)
    print("Task added!")

# Check tasks
def check_tasks():
    print("\nToday's Tasks:")
    for i, task in enumerate(tasks):
        status = "✅" if task["done"] else "❌"
        print(f"{i+1}. {task['task']} - {status}")

    for i, task in enumerate(tasks):
        if not task["done"]:
            done = input(f"Did you complete: '{task['task']}'? (y/n): ")
            if done.lower() == 'y':
                task["done"] = True
    save_tasks(tasks)

# Alarm check
def alarm_check():
    now = datetime.now().strftime("%H:%M")
    for task in tasks:
        if task["time"] == now and not task["done"]:
            notification.notify(
                title="To-Do Reminder!",
                message=task["task"],
                timeout=10
            )

# Edit task
def edit_task():
    if not tasks:
        print("No tasks to edit.")
        return

    print("\nTasks:")
    for i, task in enumerate(tasks):
        status = "✅" if task["done"] else "❌"
        print(f"{i+1}. {task['task']} - {status} - Alarm: {task['time']}")

    try:
        idx = int(input("Enter the task number to edit: ")) - 1
        if 0 <= idx < len(tasks):
            task = tasks[idx]
            print("Leave input blank if you don't want to change it.")

            new_name = input(f"New task name (current: {task['task']}): ")
            new_time = input(f"New alarm time (current: {task['time']}): ")
            new_status = input(f"Is task done? (y/n, current: {'y' if task['done'] else 'n'}): ")

            if new_name:
                task['task'] = new_name
            if new_time:
                task['time'] = new_time
            if new_status.lower() in ['y', 'n']:
                task['done'] = new_status.lower() == 'y'

            save_tasks(tasks)
            print("Task updated!")
        else:
            print("Invalid task number.")
    except ValueError:
        print("Please enter a valid number.")

# Main Menu
tasks = load_tasks()

print("\n--- To-Do List with Daily Alarm ---")
while True:
    alarm_check()  # Check alarms before showing menu

    print("\nMenu:\n1. Add Task\n2. Daily Check\n3. Edit Task\n4. Exit")
    choice = input("Choose an option: ")

    if choice == '1':
        add_task()
    elif choice == '2':
        check_tasks()
    elif choice == '3':
        edit_task()
        break
    elif choice == '4':
        print("Goodbye! 😊")
        break
    else:
        print("Invalid choice. Try again.")
