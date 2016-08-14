<?php
	session_start();
	
	if (isset($_SESSION['user'])) {
		header( 'Location: index.php' ) ;
		exit;
	}
	if (!isset($_SESSION['admin'])) {
		header( 'Location: index.php' ) ;
		exit;
	}
	
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
		include("estrenos.php");
	?>
		<div class="admini">
			<?php
			
			
			if($con=mysql_connect(HOST,USER,PASS)){
				mysql_select_db(videoclub1080p,$con);
				mysql_query("SET NAMES 'utf8'");
				
				$consulta="(SELECT * FROM usuarios where activo='0')";
				if($result=mysql_query($consulta)){
					while($fila=mysql_fetch_array($result)){
						echo "<div class=user_active>";
						echo '<a href="activarusuario.php?dni='.$fila[dni].'"><p>--> '.$fila[nombre].' '.$fila[dni].' Pinchar aquí para ACTIVAR</p></a>';
						echo "</div>";
					}
				}
			}
			?>
		</div>				
	</div>
</div>
<?php
	include("scripts.php");
?>
</body>
</html>