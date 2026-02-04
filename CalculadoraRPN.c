#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_SIZE 8
#define PI 3.1416

/* ====== Pila ====== */
float stack[STACK_SIZE];
int top = -1;

/* ====== Prototipos ====== */
void push(float value);
float pop(void);
int isEmpty(void);
void printStack(void);
void processOperator(char op);

/* ====== Función principal ====== */
int main(void)
{
    char input;

    printf("Calculadora RPN\n");
    printf("Operandos: +  -  *  /\n");
    printf("Funciones: r(raiz) s(seno) c(coseno) t(tan) p(potencia)\n");
    printf("Ingrese q para salir\n\n");

    while (1)
    {
        printf("> ");
        scanf(" %c", &input);

        if (input == 'q')
        {
            break;
        }

        if ((input >= '0' && input <= '9') || input == '.')
        {
            ungetc(input, stdin);
            float number;
            scanf("%f", &number);
            push(number);
        }
        else
        {
            processOperator(input);
        }

        printStack();
    }

    return 0;
}

/* ====== Manejo de pila ====== */
void push(float value)
{
    if (top >= STACK_SIZE - 1)
    {
        printf("Error: pila llena\n");
        return;
    }
    stack[++top] = value;
}

float pop(void)
{
    if (isEmpty())
    {
        printf("Error: pila vacía\n");
        return 0.0f;
    }
    return stack[top--];
}

int isEmpty(void)
{
    return top == -1;
}

/* ====== Operaciones ====== */
void processOperator(char op)
{
    float a, b;

    switch (op)
    {
        case '+':
            b = pop();
            a = pop();
            push(a + b);
            break;

        case '-':
            b = pop();
            a = pop();
            push(a - b);
            break;

        case '*':
            b = pop();
            a = pop();
            push(a * b);
            break;

        case '/':
            b = pop();
            a = pop();
            if (b == 0)
            {
                printf("Error: división por cero\n");
                push(a);
                push(b);
            }
            else
            {
                push(a / b);
            }
            break;

        case 'r':   /* raíz cuadrada */
            a = pop();
            if (a < 0)
            {
                printf("Error: raíz de número negativo\n");
                push(a);
            }
            else
            {
                push(sqrt(a));
            }
            break;

        case 's':   /* seno (grados) */
            a = pop();
            push(sin(a * PI / 180.0));
            break;

        case 'c':   /* coseno (grados) */
            a = pop();
            push(cos(a * PI / 180.0));
            break;

        case 't':   /* tangente (grados) */
            a = pop();
            push(tan(a * PI / 180.0));
            break;

        case 'p':   /* potencia */
            b = pop();
            a = pop();
            push(pow(a, b));
            break;

        default:
            printf("Operador no válido\n");
            break;
    }
}

/* ====== Mostrar pila ====== */
void printStack(void)
{
    int i;

    printf("Pila:\n");
    for (i = top; i >= 0; i--)
    {
        printf("%d: %f\n", i, stack[i]);
    }
    printf("\n");
}
