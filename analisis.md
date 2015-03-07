## Clasificación de variables

### Variables exógenas
#### Datos
IAM: intervalo entre arribos de 10 a 14hs
IAT: intervalo entre arribos de 14 a 20hs
TA: tiempo de atención
ganancia: ganancia obtenida de un cliente
#### Control
N: Cantidad de empleadas

### Variables endógenas
#### Estado
NS: clientes en el local
#### Resultado
GAN: ganancia total
PTE: promedio de tiempo de espera
PPS: promedio de permanencia en el local
PA: porcentaje de arrepentidos por sobre los clientes atentidos
PTO(i): promedio de tiempo ocioso empleada i, con 0 < i <= N

## Modalidad
Evento a evento, N puestos con única cola

## Tabla de eventos independientes
Eventos 	| EFNC		 | EFC	 	| COND
-----------------------------------------------------------
Llegada		|Llegada 	 |Salida(i)	| NS <= N 
-----------------------------------------------------------
Salida(i)	|	-	 |Salida(i)	| NS >= N

## Tabla de eventos futuros
TPLL: tiempo de próxima llegada
TPS(i): tiempo de próxima salida por empleada i

