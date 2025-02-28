// #include "lista_tecnicos.h"
// #include "lista_usuarios.h"
// #include <stdio.h>
// #include <string.h>

// int main(int argc, char const *argv[])
// {
//     ListaTecnicos *listaTecnicos = lista_tecnicos_criar();
//     ListaUsuarios *listaUsuarios = lista_usuarios_criar();

//     char op = 0;

//     while (1)
//     {
//         scanf("%c%*c", &op);

//         if (op == 'F')
//             break;

//         if (op == 'E')
//         {
//             char acao[20] = "";
//             scanf("%[^\n]%*c", acao);

//             if (strcmp(acao, "TECNICOS") == 0)
//                 lista_tecnicos_print(listaTecnicos);

//             else if (strcmp(acao, "USUARIOS") == 0)
//                 lista_usuarios_print(listaUsuarios);
//         }

//         else if (op == 'T')
//         {
//             Tecnico *tecnico = tecnico_ler();
//             listaTecnicos = lista_tecnicos_adicionar(listaTecnicos, tecnico);
//         }

//         else if (op == 'U')
//         {
//             Usuario *usuario = usuario_ler();
//             listaUsuarios = lista_usuarios_adicionar(listaUsuarios, usuario);
//         }
//     }

//     lista_tecnicos_free(listaTecnicos);
//     lista_usuarios_free(listaUsuarios);

//     return 0;
// }
