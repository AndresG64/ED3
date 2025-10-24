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
