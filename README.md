# Proyecto estación de soldadura.
Estación de soldadura con funcionalidades como establecer punto de temperatura y automatizaciones de seguridad.

## Funcionalidades:

- **Mango Cautín:** Aprovechando la casi linealidad entre el voltaje y temperatura del cautín es posible establecer una temperatura adecuada por medio de un PWM. (El Hakko 936 tiene un una resistencia interna o termopar K, que cambia según la temperatura).
- **Pantalla LCD:** Visualización en la pantalla del set point y temperatura actual.
- **Acelerómetro:** Detección de uso o actividad para desactivar el cautín de manera automática, establecer un modo reposo y bajar el consumo. Para calcular un golpe, active una alarma y desactive el sistema.
	
## Materiales:
- *Raspberry pi pico*
- *Fuente 24V 3A:* Alimentación del cautín.
- *Fuente 3.3V:* Para controlar la parte de control.
- *Hakko 936 50W*
- *Soporte para Cautín*
- *Pantalla LCD*
- *Módulo Acelerómetro ADXL335 análogo:* Control ADC de la raspberry pi pico.
- *Caja*
- *Mosfet de alta potencia:* Para el cautín.
- *Optocoplador:* Separamos la parte de control con la de potencia.
- *Leds:* Encendido o reposo.
- *Potenciometro:* Mediante el ADC regular la temperatura.

## Motivo
Pienso que es un proyecto que cumple con los requisitos y además útil para mi carrera, donde los materiales y conocimiento se seguirán usando en la carrera. También implementando métodos de seguridad y ahorro de energía puedo tener un cautín de alta gama por un precio reducido y hecho por mi.

# Informe Proyecto Final

## Resumen
Estación de soldadura basada en un control PID con lazo cerrado de retroalimentación. Se implementa la lectura por ADC para definir el setpoint y una salida PWM controlada por el PID para alcanzar la temperatura solicitada. Además, se mide continuamente el voltaje generado por la resistencia interna del cautín, el cual varía con la temperatura, con el fin de calcular el error actual y corregirlo en tiempo real.

## Procedimiento experimental y resultados

### Caracterización del Cautín
Para caracterizar la resistencia interna del cautín se implementó un programa utilizando el protocolo de comunicación SPI en conjunto con el módulo MAX6675, con el fin de capturar la temperatura medida por una termocupla. Esto permitió conectar el cautín directamente a 24 V y registrar tanto la variación de su resistencia como la temperatura de la punta, apoyándola sobre la termocupla. A partir de este procedimiento se obtuvo una tabla de Resistencia vs. Temperatura.

Posteriormente, empleando Excel fue posible calcular la relación entre temperatura y voltaje considerando una resistencia fija en serie de 1 kΩ y una alimentación de 3.3 V, correspondiente a la salida de la Raspberry Pi Pico. Sin embargo, la variación de voltaje dentro del rango de trabajo resultó muy pequeña, lo que reducía significativamente la resolución del ADC.

Para corregir esto, se optó por aprovechar completamente el rango del ADC mediante un amplificador operacional MOC6002 configurado en modo no inversor con una ganancia de 5. De esta manera, se amplificó la señal para obtener una mayor sensibilidad y una mejor resolución en la medición de temperatura.

### Etapa de potencia y control
Para garantizar un funcionamiento seguro y evitar fallos en el montaje, se consideró necesario separar la etapa de control de la etapa de potencia. Para ello se implementó un optoacoplador 4n26 que trabajará a una frecuencia de 1KHz, cuya salida opera a 5V mediante un convertidor reductor LM2596, elegido por su buena capacidad de disipación cuando se trabaja con 24 V de entrada.

La etapa de conmutación utiliza un transistor 2N2222 junto con un MOSFET IRF3708, el cual entra en conducción plena con un voltaje de compuerta cercano a 4.4 V y una resistencia serie de 110 Ω. Este arreglo permite controlar adecuadamente la corriente, habilitando o bloqueando el paso entre el drenaje y la fuente del MOSFET. Su uso también es conveniente debido a la salida invertida del optoacoplador, situación que se corrige empleando el transistor en configuración adecuada. Además, se incorporó una resistencia pull-down en la compuerta para asegurar que el MOSFET permanezca apagado cuando el transistor no está activo.

### Control PID
En la etapa de control se realiza la lectura, mediante el ADC, de un potenciómetro de 10 kΩ conectado a 3.3 V del microcontrolador. Este voltaje se convierte de forma lineal a una temperatura dentro del rango establecido. El valor obtenido se utiliza como referencia para calcular el error frente a la temperatura medida en el cautín y aplicar las acciones proporcional, integral y derivativa necesarias.

Las constantes del PID se determinaron experimentalmente. Se inició ajustando la ganancia proporcional con valores muy bajos para observar si el sistema respondía con lentitud o si lograba alcanzar el setpoint. La ganancia Kp seleccionada proporciona una respuesta rápida y mantiene la temperatura dentro de un margen cercano al 5% del valor deseado. Para reducir las oscilaciones se ajustó la ganancia integral, eligiendo un valor aún menor, lo que permitió alcanzar una tolerancia aproximada del 2%, adecuada para este tipo de control. La ganancia derivativa no fue necesaria debido a la buena estabilidad obtenida con las acciones proporcional e integral.

## Conclusiones
-   El análisis experimental del comportamiento de las ganancias del control PID es posible a partir del ensayo y visualización del comportamiento a través del monitor serial para corregir y establecer parámetros.

-   La carácterización de la tabla Resistencia vs Temperatura fue buena práctica para interpolar y tomar la decición de amplificar la salida con el fin de ganar mas resolución.

-   El uso del optocoplador 4n26 resultó trabajar bien a frecuencia de 1Khz aún teniendo una respuesta lenta y carácterizado al tener corrientes de fuja a frecuencias altas.





