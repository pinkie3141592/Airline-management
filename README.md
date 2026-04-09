# Restaurant Management System

## Description

This program is a restaurant management system developed in C. It allows an administrator to manage menu items, register customer orders, consult stored orders, and generate sales reports. The system uses a menu-based interface and stores data in binary files.

## Features

* User login system (default admin account)
* Add and view menu items (platillos)
* Register customer orders with multiple dishes
* Calculate total cost of each order automatically
* Consult orders by different criteria
* Generate general sales reports
* Export a detailed report to a text file

## How to Use

When the program starts, you must log in:

Default credentials:
Usuario: admin
Contraseña: 1234

After logging in, the main menu provides the following options:

1. Gestionar menú del restaurante
   Allows you to add new dishes and view the current menu.

2. Registrar nuevo pedido
   Lets you create a new order by entering the client name and selecting dish IDs. The program calculates the total automatically.

3. Consultar pedidos realizados
   Allows you to:

   * View all orders
   * Search orders by client
   * Search orders by date range
   * View most sold dishes

4. Generar reporte de ventas
   Displays a summary of total orders, total sales, and average sales. It also generates a text file with detailed order information.

5. Salir
   Closes the program.

## Data Storage

The program uses binary files to store information:

usuarios.bin: stores user credentials
platillos.bin: stores menu items
pedidos.bin: stores customer orders
reporte_pedidos.txt: generated report with readable order details

## How to Compile and Run

```bash
gcc main.c gestion.c pedidos.c utilidades.c validaciones.c -o program
program
```

Make sure all header (.h) and source (.c) files are included in the same directory or properly referenced.

## Notes

* You must register menu items before creating orders
* The system validates inputs to prevent invalid data
* Orders include date and time automatically
* Reports group orders by date and calculate total sales

## Technologies Used

C programming language
Binary file handling
Structured programming with multiple modules

