# 🌳 Proyecto Arboles - Familia Adarme-Aguillón

Un sistema de gestión de árbol genealógico para la **Familia Adarme-Aguillón**, implementado en C++ utilizando estructuras de datos de árbol binario. Este proyecto permite visualizar la línea de sucesión, gestionar el estado del Don y editar miembros de la familia de manera eficiente.

## 📋 Descripción

Este programa simula la jerarquía de una familia mafiosa, donde cada miembro tiene un rol específico en la estructura familiar. Utiliza un árbol binario para representar las relaciones parentales y de sucesión, permitiendo operaciones como:

- Carga de datos desde un archivo CSV
- Visualización de la línea de sucesión viva
- Protocolo automático de sucesión del Don
- Edición de datos de miembros individuales

El proyecto está diseñado con una interfaz de consola colorida y fácil de usar, inspirada en temas de mafia clásica.

## ✨ Características

- **📊 Carga de Datos**: Importa información familiar desde un archivo CSV estructurado
- **👑 Gestión de Sucesión**: Algoritmo inteligente para determinar el próximo Don basado en reglas de herencia
- **🔍 Visualización Jerárquica**: Muestra la línea de sucesión en formato de árbol
- **✏️ Edición en Tiempo Real**: Modifica datos de miembros existentes
- **🎨 Interfaz Colorida**: UI con colores ANSI para una experiencia visual atractiva
- **🛡️ Validación de Datos**: Manejo robusto de errores y datos faltantes

## 🛠️ Requisitos del Sistema

- **Compilador**: GCC (MinGW en Windows) o cualquier compilador C++17 compatible
- **Sistema Operativo**: Windows, Linux o macOS
- **Dependencias**: Ninguna externa (solo librerías estándar de C++)

## 🚀 Instalación y Compilación

### 1. Clonar el Repositorio
```bash
git clone https://github.com/tu-usuario/proyecto-mafia.git
cd proyecto-mafia
```

### 2. Compilar el Proyecto
Usando el compilador GCC incluido en el proyecto:

```bash
# Desde la raíz del proyecto
gcc -fdiagnostics-color=always -g src/main.cpp src/mafia_tree.cpp -o bin/programa_mafia.exe
```

O utilizando el task de VS Code:
- Presiona `Ctrl+Shift+P` y selecciona "Tasks: Run Task"
- Elige "C/C++: gcc.exe compilar archivo activo"

### 3. Ejecutar el Programa
```bash
./bin/programa_mafia.exe
```

## 📖 Uso

Al ejecutar el programa, se presenta un menú principal con las siguientes opciones:

1. **Ver Línea de Sucesión**: Muestra la jerarquía familiar actual de miembros vivos
2. **Estado del Don (Sucesión)**: Ejecuta el protocolo de sucesión si el Don actual ha fallecido
3. **Editar Miembro**: Modifica los datos de un miembro específico por ID
4. **Salir**: Cierra el programa

### Formato del Archivo CSV

El archivo `bin/datos_familia.csv` debe tener el siguiente formato:

```csv
id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss
1,Victor,Adarme-Aguillon,H,70,0,0,0,0,1
2,Ruben,Adarme-Aguillon,H,55,1,0,0,0,0
...
```

**Campos:**
- `id`: Identificador único del miembro
- `name`: Nombre
- `last_name`: Apellido
- `gender`: Género (H/M)
- `age`: Edad
- `id_boss`: ID del jefe directo (0 para el Don original)
- `is_dead`: Estado de vida (0=vivo, 1=muerto)
- `in_jail`: Estado de encarcelamiento (0=libre, 1=preso)
- `was_boss`: Si fue Don anteriormente (0=no, 1=sí)
- `is_boss`: Si es el Don actual (0=no, 1=sí)

