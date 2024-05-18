explicacao do MatrixCreator:

 00000 11111 00000

j+1 --> por causa do \n do comeco
j+1 + (i * info.largura) --> para percorrer as linhas
j+1 + (i * info.largura) + i --> a cada troca de linha ha mais um \n

a logica para acesso de info.matriz esta correta
o problema eh na parte de atribuicao, por algum motivo add 48 ao numero
checar depois oq ue eh que acontece.