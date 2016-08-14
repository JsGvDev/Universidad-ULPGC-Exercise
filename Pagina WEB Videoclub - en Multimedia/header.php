<div class="cabecera">
<div id="menu">
<ul id="nav">
	<li><a href="http://localhost/videoclub/index.php">inicio</a></li>
	<li><a href="#">Películas</a>
		<ul>
			<li><a href="http://localhost/videoclub/novedades.php">Novedades</a>
				<ul>
					<li><a href="http://localhost/videoclub/novedades.php?soporte=Bluray">BluRay</a></li>
					<li><a href="http://localhost/videoclub/novedades.php?soporte=DVD">DVD</a></li>
					<li><a href="http://localhost/videoclub/novedades.php?soporte=Series">Series TV</a></li>
				</ul>
			</li>
			<li><a href="http://localhost/videoclub/generos.php">Generos</a>
				<ul>
				<?php
					if($con=mysql_connect(HOST,USER,PASS)){
						mysql_select_db(videoclub1080p,$con);
						mysql_query("SET NAMES 'utf8'");
						
						$consulta="(SELECT * FROM categorias)";
						if($result=mysql_query($consulta)){ 
							while(($fila=mysql_fetch_array($result))){							
								echo '<li><a href="http://localhost/videoclub/categorias.php?categoria='.$fila['slugcategorias'].'">'.$fila['categoria'].'</a></li>';					
							}
						}
					}

				?>
				</ul>
			</li>
		</ul>
	</li>
	<li><a href="http://localhost/videoclub/calendario.php">Calendario</a></li>  
	<li><a href="http://www.imdb.es/news/">Noticias</a></li>
	<li><a href="#">Servicios</a>
		<ul>
			<li><a href="#">Reparación Discos</a>
				<ul><li><a href="#">3,00 € Und. (DVD)</a></li></ul>
			</li>
		</ul>
	</li>
	<li><a href="#">Contacto</a></li>
	<?php if (isset($_SESSION['admin'])){?>
		<li><a href="admin.php">Administración</a></li>
	<?php } ?>
</ul>
</div>
</div>
