🎟️ Control de Ingreso a Evento – Segundo Parcial AyED
Algoritmos y Estructura de Datos – UTN – Ingeniería en Sistemas
📅 Segundo Parcial | 10/11/2025 | Tema 1

📋 Descripción
Simulación del sistema de control de ingreso de espectadores a un evento al aire libre, implementado en C. El programa modela el flujo completo del personal de seguridad: desde el escaneo de tickets QR hasta la generación de estadísticas de asistencia por zona.
Los espectadores cuentan con tres tipos de ubicaciones: A, B y C.

🧠 Estrategia de resolución
1. Generar la lista de entradas vendidas (lista enlazada)
2. Crear la cola de espera de ingreso
3. Leer los números de ticket escaneados:
   a. Buscar en la lista de entradas vendidas
   b. Si se encuentra, encolar al espectador
4. Crear las listas por zona (A, B, C)
5. Desencolar los tickets e insertarlos de forma ordenada
   en la lista correspondiente según su zona
6. Contar tickets que NO asistieron (los que quedaron en la lista original)
7. Contar espectadores por cada zona
8. Calcular el porcentaje de asistencia
9. Mostrar estadísticas por zona

⚙️ Funcionalidades

Carga de entradas vendidas – lista enlazada con número de ticket y zona asignada.
Cola de espera – los espectadores que pasan el primer control se encolan.
Listas ordenadas por zona – en el segundo control, cada espectador se inserta ordenadamente en la lista de su zona (A, B o C).
Cierre de ingreso – al iniciar el evento no se permiten más ingresos.
Estadísticas de control (función recursiva):

Porcentaje de espectadores que asistieron sobre el total vendido.
Cantidad de espectadores por zona.

📌 Notas

La función de conteo de espectadores por zona fue implementada de forma recursiva, tal como lo requiere el enunciado.
Se utilizan listas enlazadas simples, colas FIFO y listas ordenadas como estructuras principales.


👤 Lilen C.
Trabajo realizado para la materia Algoritmos y Estructura de Datos
UTN – Facultad Regional La Plata | Ingeniería en Sistemas de Información
