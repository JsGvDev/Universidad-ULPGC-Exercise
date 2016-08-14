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
	$dni = $_POST["dni"];
	$pwd = md5($_POST["clave"]);


	if($con=mysql_connect(HOST,USER,PASS)){
			mysql_select_db(videoclub1080p,$con);
			mysql_query("SET NAMES 'utf8'");
			
			$consulta=("SELECT * FROM usuarios WHERE dni='".$dni."' AND pwd='".$pwd."'");
			if($result=mysql_query($consulta)){
				if(mysql_num_rows($result) > 0){
					//session_start();
					$fila=mysql_fetch_array($result);
					if ($fila['activo'] > 0) {
						if ($fila['tipousuario'] == 'cliente') {
							if (!isset($_SESSION['user'])) {
								$_SESSION['user'] = $fila['nombre'];
							}
							//header( 'Location: userindex.php' ) ;
						} else {
							if (!isset($_SESSION['admin'])) {
								$_SESSION['admin'] = $fila['nombre'];
							}
							//header( 'Location: adminindex.php' ) ;
						}
						header( 'Location: index.php' ) ;
					} else {
						header( 'Location: fallologin.php?f=fallo' ) ;
					}
				} else {
					header('Location: fallologin.php');	
				}
			}			
	} else {
		echo 'Error en la conexión';
	}
			
	mysql_close($con);	
?>
