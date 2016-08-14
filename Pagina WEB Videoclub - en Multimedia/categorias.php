<?php
	session_start();
	$_SESSION['usuario']=1;
	include('macro.php');
?>
<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
	<link rel="stylesheet" type="text/css" href="listados.css" />
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
		/*include("estrenos.php");*/
		$categ='';	
		if(isset($_GET['categoria'])&&$_GET['categoria']!=''){
		echo '<div class="novedades">';
			if($con=mysql_connect(HOST,USER,PASS)){
				mysql_select_db(videoclub1080p,$con);
				mysql_query("SET NAMES 'utf8'");
				
				$consulta="(SELECT * FROM categorias where slugcategorias='" . $_GET[categoria] . "')";
				if($result=mysql_query($consulta)){
					$fila=mysql_fetch_array($result);
					echo '<img src="imagenes/categorias/g'.$fila[slugcategorias].'.png">';
					$categ=$fila[categoria];
				}
			}
		echo '</div>';
		} else {
			include("estrenos.php");
		}
	
		if($con=mysql_connect(HOST,USER,PASS)){
			mysql_select_db(videoclub1080p,$con);
			mysql_query("SET NAMES 'utf8'");
	echo"<div class=list_cat>";
			$subconsulta0='';
			$sublink0="";
			if(isset($_GET['categoria'])&&$_GET['categoria']!=''){
				$subconsulta0=" and genero = '".$categ . "' ";
				$sublink0="&categoria=".$_GET['categoria'];
			}
			$consulta="(SELECT * FROM soporte WHERE 1)";
			if($result=mysql_query($consulta)){ 
				while(($fila=mysql_fetch_array($result))){							
					echo "<div class= $fila[formato]>";
						echo "<h3>$fila[formato]</h3>";
						echo "<a href=\"categorias.php?soporte=$fila[formato]$sublink0\"><img src='$fila[imagensoporte]'width='94' height='139'></a>";
					echo "</div> ";
				}				
			}else{
				echo 'Base de datos vacía';
			}
	echo"</div>";
	include("proxestrenos.php");
	$subconsulta='';
			if(isset($_GET['soporte'])&&$_GET['soporte']!='')
				$subconsulta=" and formato = '".$_GET['soporte'] . "' ";
	echo "<div class=list_novedad>";

			$NumPelis=0;
			$npaginas=6;
			$consulta="(SELECT * FROM peliculas WHERE fechaestreno!='0000-00-00' " . $subconsulta0 . $subconsulta . ")";
			if($result=mysql_query($consulta)){
				$NumPelis=mysql_num_rows($result);
			}
			$sublink="";
			if(isset($_GET['soporte'])&&$_GET['soporte']!='')
				$sublink="&soporte=".$_GET['soporte'];

			for($i=0;$i<($NumPelis/$npaginas);$i++){
				echo '|<a href="categorias.php?pagina=' . $i . $sublink0 . $sublink . '" >--Pag' . ($i+1) . '--</a>|';
			}
			$subconsulta2=' LIMIT 0,'.$npaginas;
			if(isset($_GET['pagina'])&&$_GET['pagina']!='')
				/*$subconsulta2=" LIMIT ".($_GET['pagina']*$npaginas) . ',' .(($_GET['pagina']*$npaginas)+$npaginas); LIMIT "Valor donde inicio",  "cuantos valores muestro"*/
				$subconsulta2=" LIMIT ".($_GET['pagina']*$npaginas) . ',' .($npaginas);
			$consulta="(SELECT * FROM peliculas WHERE fechaestreno!='0000-00-00' " . $subconsulta0 . $subconsulta . " ORDER BY fechaestreno DESC" . $subconsulta2 .")";
			//echo $consulta;
			echo "<ul>";
			if($result=mysql_query($consulta)){ 
				while(($fila=mysql_fetch_array($result))){
					echo "<li>";
						echo "<h4>&nbsp; $fila[genero]: &nbsp;&nbsp; $fila[titulo]</h4>";
						echo '<a href="vistapeli.php?slugpeliculas='.$fila[slugpeliculas].'"><img src="'.$fila[imagenpeli].'" width=94 height=139></a>';
						echo "<h5>&nbsp; Director: </h5>";
						echo "<p>&nbsp; $fila[director]</p>";
						echo "<h5>&nbsp; Actores: </h5>";
						echo "<p>$fila[actores]</p>";
					echo "</li>";
				}				
			}else{
				echo 'Base de datos vacía';
			}
		echo"</ul>";
		echo'<div style="clear: both";></div>';
	echo"</div>";
		}else{
			echo 'Error en la conexión';
		}
	?>
	</div>
<?php
	include("carrusel.php");	
	include("banners.php");
?>
</div>
<?php
	include("scripts.php");
?>
</body>
</html>