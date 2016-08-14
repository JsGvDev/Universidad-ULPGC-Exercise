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
			if($con=mysql_connect(HOST,USER,PASS)){
				mysql_select_db(videoclub1080p,$con);
				mysql_query("SET NAMES 'utf8'");
				$consulta="SELECT * FROM categorias WHERE slugcategorias = 'accion' OR slugcategorias = 'comedia' OR slugcategorias = 'aventura' OR slugcategorias = 'drama' OR slugcategorias = 'cienciaficcion' OR slugcategorias = 'romance' OR 
				slugcategorias = 'terror' OR slugcategorias = 'thriller' OR slugcategorias = 'animacion'";
					if($result=mysql_query($consulta)){
						while(($fila=mysql_fetch_array($result))){
							echo "<div class= $fila[categoria]>";
							echo "<h3>$fila[categoria]</h3>";
							switch ($fila[categoria]) {
								case "Acción":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=accion><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
								case "Comedia":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=comedia><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
								case "Aventura":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=aventura><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
								case "Drama":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=drama><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
								case "Ciencia-Ficción":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=cienciaficcion><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
								case "Romance":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=romance><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
								case "Terror":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=terror><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
								case "Thriller":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=thriller><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
								case "Animación":
									echo "<a href=http://localhost/videoclub/categorias.php?categoria=animacion><img src='$fila[imagencat]'width='94' height='139'></a>";
									break;
							}
							echo "</div> ";
						}
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