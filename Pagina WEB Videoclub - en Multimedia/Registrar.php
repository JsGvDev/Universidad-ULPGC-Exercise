<?php
	
	session_start();
	
	if (isset($_SESSION['user'])) {
		header( 'Location: index.php' ) ;
		exit;
	}
	if (isset($_SESSION['admin'])) {
		header( 'Location: index.php' ) ;
		exit;
	}
	include('macro.php');
	
	$nombre = $_POST["nombre"];
	$apodo = $_POST["username"];
	$dni = $_POST["userdni"];
	$pwd = md5($_POST["password"]);
	$email = $_POST["email"];
	$tlf = $_POST["tlf"];
	$activo = 0;
		
	if($con=mysql_connect(HOST,USER,PASS)){
		mysql_select_db(videoclub1080p,$con);
		mysql_query("SET NAMES 'utf8'");
			
		$consulta=("SELECT dni FROM usuarios WHERE dni='".$_POST["userdni"]."'");
		if($result=mysql_query($consulta)){
			if(mysql_num_rows($result) > 0){
				header('Location: falloregistro.php');						
			} else {
				mysql_query("insert into usuarios (nombre,apodo,dni,pwd,email,telefono,tipousuario,activo) values ('$nombre','$apodo','$dni','$pwd','$email','$tlf','cliente','$activo')",$con);			
			}
		}			
	} else {
		echo 'Error en la conexión';
	}
			
	mysql_close($con);
?>
<!DOCTYPE html>
<html>
<head>
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
	<link rel="stylesheet" type="text/css" href="mystile.css" />
	<link rel="stylesheet" type="text/css" href="registro_css.css">
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
			<h3>Registro Realizado</h3>
			<p>Se ha registrado el usuario correctamente.</p>				
		</div>
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