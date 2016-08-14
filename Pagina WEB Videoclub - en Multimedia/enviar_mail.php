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
	
	$dni = $_POST["userdni"];
		
	if($con=mysql_connect(HOST,USER,PASS)){
		mysql_select_db(videoclub1080p,$con);
		mysql_query("SET NAMES 'utf8'");
			
		$consulta=("SELECT pwd,email FROM usuarios WHERE dni='".$_POST["userdni"]."'");
		if($result=mysql_query($consulta)){
			if(mysql_num_rows($result) > 0){
				$fila=mysql_fetch_array($result);
				$email = $fila['email'];
				$pwd = md5($fila['pwd']);
				
				$from = "From: videoclub1080p@dominio.com\r\n";
				$sms = "Tú password es ".$pwd."\r\n Borra este correo por seguridad";
				
				mail($email, 'Videclub1080p: Olvido Clave', $sms, $from);
				$resp=1;
			} else {
				$resp=0;
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
		if ($resp>0) {
	?>
		<div class="contenido">
			<h3>Clave Enviada</h3>
			<p>Se ha enviado la clave correctamente.</p>
		</div>
	<?php } else { ?>
		<div class="contenido">
			<h3>Fallo Envio</h3>
			<p>El usuario es incorrecto. Por favor, vuelva a intentarlo.</p>
		</div>
		<a href="olvide_pwd.php">
			<div class="buttom"><input name=registrar type=submit value='Volver'> <br>
			</div>
		</a>
	<?php } ?>
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