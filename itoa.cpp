#include "itoa.h" //referência do header
#include <climits> // para INT_MIN e INT_MAX

char* itoa(int Value, int Base)
{          
    //a função precisa alocar a string e retorná-la
    //quem chamou a fução é responsável por imprimir e dar delete[]
    //Como calcular o tamanho necessário:
    //counter + 1 (último quociente) + 1 (se negativo, o '-') + 1 (o '\0')
    //o Array guarda números inteiros mas char* precisa de caracteres. O caractere '0' tem valor ASCII 48.
    //é preciso somar '0' + dígito para obter o char correto    

    //edgecases:
    
    //se o valor for == 0
    //base inválida, se for diferene de 8, 10 ou 16
    //valor negativo, guardar a info do valor negativo, trabalhar com o valor positivo e adicionar o sinal no final
    //INT_MIN -2147483648
    
    bool negative = false;
    unsigned int uValue; //precisa usar unsigned int pra não dar overflow na hora de mudar de sinal do INT_MIN
    char* result;    

    if (Value == 0) //edge case para valor == 0
    {
        result = new char[2]; //tamanho 2, 0 + \0
        result[0] = '0';
        result[1] = '\0'; //usa-se '\0' pra delimitar quando acaba o array
        return result;        
    }    

    if (Value < 0) //edgecase para valores negativos
    {        
        if (Value == INT_MIN) // edge case INT_MIN - 2147483648
        {
            uValue = static_cast<unsigned int>(INT_MAX) + 1u; // 2147483647 unsigned + 1u = 2147483648, não dá overflow       
        }   
        else //conversão para unsigned para todos os outros valores negativos
        {
            uValue = static_cast<unsigned int>(-Value); // converte pra unsigned também para padronizar
        }

        negative = true;
       
    }
    else //conversão pra unsigned caso o valor seja positivo
    {
        uValue = static_cast<unsigned int>(Value);
    }

    if (Base != 10 && Base != 8 && Base != 16) // edgecase para base inválida
    {
        return nullptr;
    }

    //função para base 10 
    if (Base == 10)
    {       
        //base 10 precisa converter usando divisões sucessivas, lê o resto de trás pra frente
        unsigned int remainder;
        unsigned int quotient;
        unsigned int uBase = static_cast<unsigned int>(Base); //declaração da variável Base como unsigned para comparação
        int charIndex = 0;

        if (uValue < uBase) //caso o value seja menor que a base, retorna o próprio value
        {                    
            //calcular o tamanho do index e alocar o result
            int length = 1 + (negative ? 1 : 0) + 1; //se negative for verdadeiro adiciona 1, 0 se positivo, +2 do value e do \0
            result = new char[length]; //operador new para alocar na memória

            if (negative)
            {
                result[charIndex++] = '-'; //escreve o sinal negativo no result           
            }

            result[charIndex++] = '0' + uValue; // converte o número para o caractere correspondente
            result[charIndex] = '\0'; //usa-se '\0' pra delimitar quando acaba a string
            return result;
        }

        size_t size = 10; //valor inicial padrão
        unsigned int* myArray = new unsigned int[size]; //aloca dinamicamente a variável para o número de divisões

        size_t counter = 0;       

        do //usar do while garante que o loop execute pelo menos uma vez antes de checar a condição
        {
            if (counter >= size) //se verdadeiro, estourou a capacidade máxima -> sobra de tamanho
            {
                size *= 2; //dobra a capacidade, padrão para manipulação de memória dinâmica

                unsigned int* temp = new unsigned int[size]; //copia os dados velhos e aloca na memória nova

                for (size_t i = 0; i < counter; i++)
                {
                    temp[i] = myArray[i];
                }

                delete[] myArray; //libera memória e evita leaks  
                myArray = temp;
            }

            quotient = uValue / uBase;
            remainder = uValue % uBase;
            myArray[counter] = remainder; //adiciona o resto da divisão no array    
            uValue = uValue / uBase;
            counter++;

        } while (quotient >= uBase);  //precisa verificar se o quociente é maior ou igual à base pra poder dividir novamente    

        //calcular o tamanho do index e alocar o result
        int length = counter + 1 + (negative ? 1 : 0) + 1; //se negative for verdadeiro adiciona 1, 0 se positivo, +2 do quociente e do \0
        result = new char[length]; //operador new para alocar na memória
               
        if (negative)
        {
            result[charIndex++] = '-'; //escreve o sinal negativo no result           
        }

        result[charIndex++] = '0' + quotient; // adiciona o último quociente           

        for (int i = counter - 1; i >= 0; i--) //percorre o array de trás pra frente, começa em 0 o primeiro elemento
        {
            result[charIndex++] = '0' + myArray[i]; //adiciona cada um dos dígitos ao result                     
        }

        result[charIndex] = '\0'; //termina a string
        delete[] myArray;  //libera memória e evita leaks 
        return result;       
    }    

    //função para base 8 
    if (Base == 8)
    {
        //base 8 precisa converter usando divisões sucessivas, lê o resto de trás pra frente
        unsigned int remainder;
        unsigned int quotient;
        unsigned int uBase = static_cast<unsigned int>(Base); //declaração da variável Base como unsigned para comparação
        int charIndex = 0;

        if (uValue < uBase) //caso o value seja menor que a base, retorna o próprio value
        {
            //calcular o tamanho do index e alocar o result
            int length = 1 + (negative ? 1 : 0) + 1; //se negative for verdadeiro adiciona 1, 0 se positivo, +2 do value e do \0
            result = new char[length]; //operador new para alocar na memória

            if (negative)
            {
                result[charIndex++] = '-'; //escreve o sinal negativo no result           
            }

            result[charIndex++] = '0' + uValue; // converte o número para o caractere correspondente
            result[charIndex] = '\0'; //usa-se '\0' pra delimitar quando acaba a string
            return result;
        }

        size_t size = 10; //valor inicial padrão
        unsigned int* myArray = new unsigned int[size]; //aloca dinamicamente a variável para o número de divisões

        size_t counter = 0;           

        do //usar do while garante que o loop execute pelo menos uma vez antes de checar a condição
        {
            if (counter >= size) //se verdadeiro, estourou a capacidade máxima -> sobra de tamanho
            {
                size *= 2; //dobra a capacidade, padrão para manipulação de memória dinâmica

                unsigned int* temp = new unsigned int[size]; //copia os dados velhos e aloca na memória nova

                for (size_t i = 0; i < counter; i++)
                {
                    temp[i] = myArray[i];
                }

                delete[] myArray; //libera memória e evita leaks  
                myArray = temp;
            }

            quotient = uValue / uBase;
            remainder = uValue % uBase;
            myArray[counter] = remainder; //adiciona o resto da divisão no array    
            uValue = uValue / uBase;
            counter++;

        } while (quotient >= uBase);  //precisa verificar se o quociente é maior ou igual à base pra poder dividir novamente    

        //calcular o tamanho do index e alocar o result
        int length = counter + 1 + (negative ? 1 : 0) + 1; //se negative for verdadeiro adiciona 1, 0 se positivo, +2 do quociente e do \0
        result = new char[length]; //operador new para alocar na memória
           
        if (negative) //traz o sinal de volta
        {
            result[charIndex++] = '-'; //escreve o sinal negativo no result           
        }

        result[charIndex++] = '0' + quotient; // adiciona o último quociente        

        for (int i = counter - 1; i >= 0; i--) //percorre o array de trás pra frente, começa em 0 o primeiro elemento
        {
            result[charIndex++] = '0' + myArray[i]; //adiciona cada um dos dígitos ao result                     
        }

        result[charIndex] = '\0'; //termina a string
        delete[] myArray;  //libera memória e evita leaks 
        return result;
    }

    //função para base 16
    if (Base == 16)
    {
        //base 16 precisa converter usando divisões sucessivas, lê o resto de trás pra frente
        unsigned int remainder;
        unsigned int quotient;
        unsigned int uBase = static_cast<unsigned int>(Base); //declaração da variável Base como unsigned para comparação
        int charIndex = 0;

        //vetor manual de mapeamento dos caracteres hexadecimais       
        char hexMap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

        if (uValue < uBase) //caso o value seja menor que a base, retorna o próprio value
        {
            //calcular o tamanho do index e alocar o result
            int length = 1 + (negative ? 1 : 0) + 1; //se negative for verdadeiro adiciona 1, 0 se positivo, +2 do value e do \0
            result = new char[length]; //operador new para alocar na memória

            if (negative)
            {
                result[charIndex++] = '-'; //escreve o sinal negativo no result           
            }

            result[charIndex++] = hexMap[uValue]; //hexMap já retorna o char correto, não precisa converter
            result[charIndex] = '\0'; //usa-se '\0' pra delimitar quando acaba a string
            return result;
        }       

        size_t size = 10; //valor inicial padrão
        unsigned int* myArray = new unsigned int[size]; //aloca dinamicamente a variável para o número de divisões

        size_t counter = 0;                

        do //usar do while garante que o loop execute pelo menos uma vez antes de checar a condição
        {
            if (counter >= size) //se verdadeiro, estourou a capacidade máxima -> sobra de tamanho
            {
                size *= 2; //dobra a capacidade, padrão para manipulação de memória dinâmica

                unsigned int* temp = new unsigned int[size]; //copia os dados velhos e aloca na memória nova

                for (size_t i = 0; i < counter; i++)
                {
                    temp[i] = myArray[i];
                }

                delete[] myArray; //libera memória e evita leaks  
                myArray = temp;
            }

            quotient = uValue / uBase;
            remainder = uValue % uBase;
            myArray[counter] = remainder; //adiciona o resto da divisão no array    
            uValue = uValue / uBase;
            counter++;

        } while (quotient >= uBase);  //precisa verificar se o quociente é maior ou igual à base pra poder dividir novamente    
            
        //calcular o tamanho do index e alocar o result
        int length = counter + 1 + (negative ? 1 : 0) + 1; //se negative for verdadeiro adiciona 1, 0 se positivo, +2 do quociente e do \0
        result = new char[length]; //operador new para alocar na memória             

        if (negative) //traz o sinal de volta
        {
            result[charIndex++] = '-'; //escreve o sinal negativo no result           
        }

        result[charIndex++] = hexMap[quotient]; //já é char, não precisa do + 0              

        for (int i = counter - 1; i >= 0; i--) //percorre o array de trás pra frente, começa em 0 o primeiro elemento
        {           
            result[charIndex++] = hexMap[myArray[i]];
        }

        result[charIndex] = '\0'; //termina a string
        delete[] myArray;  //libera memória e evita leaks 
        return result;
    }   

    return nullptr; // return de segurança para o compilador
}