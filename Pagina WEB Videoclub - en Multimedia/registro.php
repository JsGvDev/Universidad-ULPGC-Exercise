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
			<h3>Registrar Usuario</h3>
			<form method="post" name="register" onSubmit="return validar()" action="Registrar.php">
				<p>Los campos que tienen un asterisco (<font color=red>*</font>) son obligatorios. </p>
				<div class="form-item">
						<label><font color=red>*</font>Nombre</label>
						<input id="name" type="text" name="nombre" maxlength="30" class="form-input">
						<div class="advert">
							<p>Solo Letras y espacios</p>
						</div>						
					</div>
					<div class="form-item">
						<label>Apodo</label>
						<input id="nick" type="text" name="username" maxlength="16" class="form-input">
						<div class="advert">
							<p>Entre 4 y 16 caracteres, sin espacios</p>
						</div>						
					</div>
					<div class="form-item">
						<label><font color=red>*</font>DNI</label>
						<input id="dni" type="text" name="userdni" maxlength="8" class="form-input">
						<div class="advert">
							<p>8 números sin caracteres</p>
						</div>						
					</div>
					<div class="form-item">
						<label><font color=red>*</font>Contraseña</label>
						<input id="password" type="password" name="password" maxlength="30" class="form-input">
						<div class="advert">
							<p>Longitud mínima de 6 caracteres</p>
						</div>						
					</div>
					<div class="form-item">
						<label><font color=red>*</font>Confirmar Contraseña</label>
						<input id="password_conf" type="password" name="password_conf" maxlength="30" class="form-input">						
					</div>
					<div class="form-item">
						<label><font color=red>*</font>Email</label>
						<input id="email" type="text" name="email" maxlength="255" class="form-input">
					</div>
					<div class="form-item">
						<label>Teléfono</label>
						<input id="tlf" type="text" name="tlf" maxlength="9" class="form-input">												
					</div>
					<p>Al registrarme acepto los <a href="terminos-y-condiciones.txt" target="_blank">términos y condiciones</a> del sitio.</p>
					<div class="buttom">
						<input name=registrar type=submit value=Registrar> <br>
					</div>				
			</form>	
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