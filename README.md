PAV - P2: detección de actividad vocal (VAD)
============================================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 2](https://github.com/albino-pav/P2),
y una parte de su gestión se realizará mediante esta web de trabajo colaborativo.  Al contrario que Git,
GitHub se gestiona completamente desde un entorno gráfico bastante intuitivo. Además, está razonablemente
documentado, tanto internamente, mediante sus [Guías de GitHub](https://guides.github.com/), como
externamente, mediante infinidad de tutoriales, guías y vídeos disponibles gratuitamente en internet.


Inicialización del repositorio de la práctica.
----------------------------------------------

Para cargar los ficheros en su ordenador personal debe seguir los pasos siguientes:

*	Abra una cuenta GitHub para gestionar esta y el resto de prácticas del curso.
*	Cree un repositorio GitHub con el contenido inicial de la práctica (sólo debe hacerlo uno de los
	integrantes del grupo de laboratorio, cuya página GitHub actuará de repositorio central del grupo):
	-	Acceda la página de la [Práctica 2](https://github.com/albino-pav/P2).
	-	En la parte superior derecha encontrará el botón **`Fork`**. Apriételo y, después de unos segundos,
		se creará en su cuenta GitHub un proyecto con el mismo nombre (**P2**). Si ya tuviera uno con ese 
		nombre, se utilizará el nombre **P2-1**, y así sucesivamente.
*	Habilite al resto de miembros del grupo como *colaboradores* del proyecto; de este modo, podrán
	subir sus modificaciones al repositorio central:
	-	En la página principal del repositorio, en la pestaña **:gear:`Settings`**, escoja la opción 
		**Collaborators** y añada a su compañero de prácticas.
	-	Éste recibirá un email solicitándole confirmación. Una vez confirmado, tanto él como el
		propietario podrán gestionar el repositorio, por ejemplo: crear ramas en él o subir las
		modificaciones de su directorio local de trabajo al repositorio GitHub.
*	En la página principal del repositorio, localice el botón **Branch: master** y úselo para crear
	una rama nueva con los primeros apellidos de los integrantes del equipo de prácticas separados por
	guion (**fulano-mengano**).
*	Todos los miembros del grupo deben realizar su copia local en su ordenador personal.
	-	Copie la dirección de su copia del repositorio apretando en el botón **Clone or download**.
		Asegúrese de usar *Clone with HTTPS*.
	-	Abra una sesión de Bash en su ordenador personal y vaya al directorio **PAV**. Desde ahí, ejecute:

		```.sh
		git clone dirección-del-fork-de-la-práctica
		```

	-	Vaya al directorio de la práctica `cd P2`.
	-	Añada la etiqueta `origin` a su copia del repositorio. Esto es útil para facilitar los *push* y
		*pull* al repositorio original:
		```.sh
		git remote add origin dirección-del-fork-de-la-práctica
		```
	-	Cambie a la rama **fulano-mengano** con la orden:

		```.sh
		git checkout fulano-mengano
		```

*	A partir de este momento, todos los miembros del grupo de prácticas pueden trabajar en su directorio
	local del modo habitual.
	-	También puede utilizar el repositorio remoto como repositorio central para el trabajo colaborativo
		de los distintos miembros del grupo de prácticas; o puede serle útil usarlo como copia de
		seguridad.
	-	Cada vez que quiera subir sus cambios locales al repositorio GitHub deberá confirmar los
		cambios en su directorio local:

		```.sh
		git add .
		git commit -m "Mensaje del commit"
		```

		y, a continuación, subirlos con la orden:

		```.sh
		git push -u origin fulano-mengano
		```

*	Al final de la práctica, la rama **fulano-mengano** del repositorio GitHub servirá para remitir la
	práctica para su evaluación utilizando el mecanismo *pull request*.
	-	Vaya a la página principal de la copia del repositorio y asegúrese de estar en la rama
		**fulano-mengano**.
	-	Pulse en el botón **New pull request**, y siga las instrucciones de GitHub.


Entrega de la práctica.
-----------------------

Responda, en este mismo documento (README.md), los ejercicios indicados a continuación. Este documento es
un fichero de texto escrito con un formato denominado _**markdown**_. La principal característica de este
formato es que, manteniendo la legibilidad cuando se visualiza con herramientas en modo texto (`more`,
`less`, editores varios, ...), permite amplias posibilidades de visualización con formato en una amplia
gama de aplicaciones; muy notablemente, **GitHub**, **Doxygen** y **Facebook** (ciertamente, :eyes:).

En GitHub. cuando existe un fichero denominado README.md en el directorio raíz de un repositorio, se
interpreta y muestra al entrar en el repositorio.

Debe redactar las respuestas a los ejercicios usando Markdown. Puede encontrar información acerca de su
sintáxis en la página web [Sintaxis de Markdown](https://daringfireball.net/projects/markdown/syntax).
También puede consultar el documento adjunto [MARKDOWN.md](MARKDOWN.md), en el que se enumeran los
elementos más relevantes para completar la redacción de esta práctica.

Recuerde realizar el *pull request* una vez completada la práctica.

Ejercicios
----------

### Etiquetado manual de los segmentos de voz y silencio

- Etiquete manualmente los segmentos de voz y silencio del fichero grabado al efecto. Inserte, a 
  continuación, una captura de `wavesurfer` en la que se vea con claridad la señal temporal, el contorno de
  potencia y la tasa de cruces por cero, junto con el etiquetado manual de los segmentos.

  <img width="1366" alt="Segmentos de Voz y Silencio" src="https://github.com/EliasEstevez/P2/blob/Estevez-Mesquida-Tarrats/Captura5.PNG"> 



- A la vista de la gráfica, indique qué valores considera adecuados para las magnitudes siguientes:

	* Incremento del nivel potencia en dB, respecto al nivel correspondiente al silencio inicial, para
	  estar seguros de que un segmento de señal se corresponde con voz.

	*Viendo la imagen, podriamos poner como todos los trozos de voz superan los 60dB en la mayoria del segmento, respecto los tramos de silencio*

	* Duración mínima razonable de los segmentos de voz y silencio.

	*La duración mínima de los segmentos de voz es de 0,5s mientras que de los segmentos de silencio seria de 0,4*

	* ¿Es capaz de sacar alguna conclusión a partir de la evolución de la tasa de cruces por cero?

	*La tasa de cruces por cero nos indica si es muy alta, la aparicion de consonantes sordas (fonema /s), también podemos observar que en los silencios, al tener un ruido alto, se muestran más picos que en los tramos de voz*


### Desarrollo del detector de actividad vocal

- Complete el código de los ficheros de la práctica para implementar un detector de actividad vocal en
  tiempo real tan exacto como sea posible. Tome como objetivo la maximización de la puntuación-F `TOTAL`.

  

- Inserte una gráfica en la que se vea con claridad la señal temporal, el etiquetado manual y la detección
  automática conseguida para el fichero grabado al efecto. 

	<img width="1366" alt="Segmentos de Voz y Silencio" src="https://github.com/EliasEstevez/P2/blob/Estevez-Mesquida-Tarrats/Captura4.PNG">

- Explique, si existen. las discrepancias entre el etiquetado manual y la detección automática.

	*En la grafica superior podemos observar que los etiquetados son similares pero no iguales. Hay una pequeña diferencia en cada una de las etiquetas de milisegundos. Podemos suponer que el vad (superior) es mucho mas preciso que el lab (inferior). Ademas alrededor del segundo 7.3 podemos ver que hay un silencio que nosotros no tuvimos en cuenta en el momento de etiquetar el audio. Para ver mas bien cual es la diferencia usamos vad_evaluation.pl que nos da la siguiente informacion:

	<img width="1366" alt="Segmentos de Voz y Silencio" src="https://github.com/EliasEstevez/P2/blob/Estevez-Mesquida-Tarrats/Captura6.PNG">

	*Vemos que los valores de voz son mas similares entre el etiquetado manual y automatico que no los valores de silencio.*

- Evalúe los resultados sobre la base de datos `db.v4` con el script `vad_evaluation.pl` e inserte a 
  continuación las tasas de sensibilidad (*recall*) y precisión para el conjunto de la base de datos (sólo
  el resumen).

	<img width="1366" alt="Segmentos de Voz y Silencio" src="https://github.com/EliasEstevez/P2/blob/Estevez-Mesquida-Tarrats/Captura7.PNG">

	*Observamos que el resultado de deteccion automatica son bastante buenos ya que el porcentage total es de 93.214%. Si analizamos valor a valor observamos que el porcentage mas bajo es de 75% pero la mayoria son mayores que 95% y por eso la media sale alta.*

### Trabajos de ampliación

#### Cancelación del ruido en los segmentos de silencio

- Si ha desarrollado el algoritmo para la cancelación de los segmentos de silencio, inserte una gráfica en
  la que se vea con claridad la señal antes y después de la cancelación (puede que `wavesurfer` no sea la
  mejor opción para esto, ya que no es capaz de visualizar varias señales al mismo tiempo).

	*Utilizamos dos ventanas de wavesurfer para comparar el señal original con el señal con 0 en los silencios*

	<img width="1366" alt="Segmentos de Voz y Silencio" src="https://github.com/EliasEstevez/P2/blob/Estevez-Mesquida-Tarrats/Captura8.PNG">

	*Por la buena calidad del microfono gran parte de los silencios ya eran cero aunque podemos apreciar algnos puntos que no (recuadro azul). Para asegurarnos de que nuestro algoritmo funciona hemos utilizado un audio aleatorio de la carpeta de datos.*
	
	<img width="1366" alt="Segmentos de Voz y Silencio" src="https://github.com/EliasEstevez/P2/blob/Estevez-Mesquida-Tarrats/Captura7.PNG">

#### Gestión de las opciones del programa usando `docopt_c`

- Si ha usado `docopt_c` para realizar la gestión de las opciones y argumentos del programa `vad`, inserte
  una captura de pantalla en la que se vea el mensaje de ayuda del programa.

	<img width="1366" alt="Segmentos de Voz y Silencio" src="https://github.com/EliasEstevez/P2/blob/Estevez-Mesquida-Tarrats/Captura10.PNG">

### Contribuciones adicionales y/o comentarios acerca de la práctica

- Indique a continuación si ha realizado algún tipo de aportación suplementaria (algoritmos de detección o 
  parámetros alternativos, etc.).

- Si lo desea, puede realizar también algún comentario acerca de la realización de la práctica que
  considere de interés de cara a su evaluación.

	En esta practica hemos tenido muchos problemas en el momento de utilizar audios nuestros. Ninguno de nosotros tiene ningunos auriculares en condiciones para grabar un audio decente. Por eso en la carpeta P2 hay una gran cantidad de audios que no llegamos a utilizar. Finalmente encontramos unos auriculares buenos y podimos grabar el audio pav_4334.wav que es el que utilizamos para la elaboración de la practica. El audio pav_1121.wav es el que utilizamos en el apartado de ampliacion, sacado de la carpeta db.v4 para poner a cero los silencios con salida ooutput.wav, el audio output.wav es el audio pav_4334 con los silencios a cero (casi igual que el audio original)

### Antes de entregar la práctica

Recuerde comprobar que el repositorio cuenta con los códigos correctos y en condiciones de ser 
correctamente compilados con la orden `meson bin; ninja -C bin`. El programa generado (`bin/vad`) será
el usado, sin más opciones, para realizar la evaluación *ciega* del sistema.
