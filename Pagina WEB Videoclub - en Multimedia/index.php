<?php
	session_start();
	$_SESSION['usuario']=1;
	include('macro.php');
?>

<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
	<link rel="stylesheet" type="text/css" href="mystile.css" />
	<link rel="stylesheet" type="text/css" href="jquery_css.css" />
	<link rel="stylesheet" type="text/css" href="jquery_css_novedad.css" />
	<script type="text/javascript" language="javascript" src="jquery/jquery.js"></script>
	<script type="text/javascript" language="javascript" src="jquery/jquery.carouFredSel-5.5.5-packed.js"></script>
	<link rel="stylesheet" type="text/css" href="JSCal2/css/jscal2.css" />
    <link rel="stylesheet" type="text/css" href="JSCal2/css/border-radius.css" />
    <link rel="stylesheet" type="text/css" href="JSCal2/css/gold/gold.css" />
	<link rel="stylesheet" type="text/css" href="reloj.css" />
    <script type="text/javascript" src="JSCal2/js/jscal2.js"></script>
    <script type="text/javascript" src="JSCal2/js/lang/es.js"></script>
<title>Videoclub 1080p</title>
</head>
<body>
<div class="principal">
<?php
	include("header.php");
?>
<div class="cuerpo"> 
	<?php
		include("lado_izq.php");
		include("estrenos.php");
	?>	
	<div class="contenido">
			<?php
			$faccion = $fcomedia = $faventura = $fdrama = $fciencia = $fromance = $fterror = $fthriller = $fanimacion = 0;
			if($con=mysql_connect(HOST,USER,PASS)){
				mysql_select_db(videoclub1080p,$con);
				mysql_query("SET NAMES 'utf8'");
				$consulta="(SELECT * FROM peliculas ORDER BY fechaestreno DESC)";
					if($result=mysql_query($consulta)){ 
						while(($fila=mysql_fetch_array($result))){
							switch ($fila[genero]) {
								case "Acción":
									if ($faccion == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=accion><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$faccion = 1;
									}									
										break;
								case "Comedia":
									if ($fcomedia == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=comedia><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$fcomedia = 1;
									}									
										break;
								case "Aventura":
									if ($faventura == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=aventura><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$faventura = 1;
									}									
										break;
								case "Drama":
									if ($fdrama == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=drama><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$fdrama = 1;
									}									
										break;
								case "Ciencia-Ficción":
									if ($fciencia == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=cienciaficcion><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$fciencia = 1;
									}									
										break;
								case "Romance":
									if ($fromance == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=romance><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$fromance = 1;
									}									
										break;
								case "Terror":
									if ($fterror == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=terror><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$fterror = 1;
									}									
										break;
								case "Thriller":
									if ($fthriller == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=thriller><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$fthriller = 1;
									}									
										break;
								case "Animación":
									if ($fanimacion == 0){
										echo "<div class= $fila[genero]>";
										echo "<a href=http://localhost/videoclub/categorias.php?categoria=animacion><h3>$fila[genero]</h3></a>";
										echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
										echo "<p>$fila[titulo]</p>";
										echo "</div> ";
										$fanimacion = 1;
									}									
										break;
									
							}
					}
						echo "</table> \n";
				}else{
						echo 'Base de datos vacía';
			}
		}else{
			echo 'Error en la conexión';
		}
		?>	
	</div>
	 
</div>
<div class="categorias" id="categorias">
	<div id="image_carousel">
		<div id="foo2">
			<div><a href="http://localhost/videoclub/categorias.php?categoria=artesmarciales"><img src="imagenes/categorias/MMA.png" alt="basketball" width="100" height="100" /><span>Artes Marciales</span></a></div>
			<div><a href="http://localhost/videoclub/categorias.php?categoria=western"><img src="imagenes/categorias/western.png" alt="beachtree" width="100" height="100" /><span>Western</span></a></div>
			<div><a href="http://localhost/videoclub/categorias.php?categoria=belica"><img src="imagenes/categorias/war.png" alt="cupcackes" width="100" height="100" /><span>Bélica</span></a></div>
			<div><a href="http://localhost/videoclub/categorias.php?categoria=historica"><img src="imagenes/categorias/historical.png" alt="hangmat" width="100" height="100" /><span>Histórica</span></a></div>
			<div><a href="http://localhost/videoclub/categorias.php?categoria=fantastico"><img src="imagenes/categorias/fantasy2.png" alt="new york" width="100" height="100" /><span>Fantástica</span></a></div>
			<div><a href="http://localhost/videoclub/categorias.php?categoria=musical"><img src="imagenes/categorias/musicals.png" alt="laundry" width="100" height="100" /><span>Musical</span></a></div>
			<div><a href="http://localhost/videoclub/categorias.php?categoria=deportiva"><img src="imagenes/categorias/sports.png" alt="mom son" width="100" height="100" /><span>Deportiva</span></a></div>
			<div><a href="http://localhost/videoclub/categorias.php?categoria=documental"><img src="imagenes/categorias/documentaries.png" alt="picknick" width="100" height="100" /><span>Documental</span></a></div>
			<div><a href="http://localhost/videoclub/categorias.php?categoria=erotica"><img src="imagenes/categorias/adult.png" alt="shoes" width="100" height="100" /><span>Erótica</span></a></div>
		</div>
		<div class="clearfix"></div>
		<a class="prev" id="foo2_prev" href="#"><span>prev</span></a>
		<a class="next" id="foo2_next" href="#"><span>next</span></a>
		<div class="pagination" id="foo2_pag"></div>
	</div> <!-- /image_carousel -->
</div>
<?php
	include("banners.php");
?>
</div>
<?php
	include("scripts.php");
?>
</body>
</html>