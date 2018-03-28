import Dependencies._

lazy val root = (project in file(".")).
	settings(
		inThisBuild(List(
			organization := "com.nextialab",
			scalaVersion := "2.12.4",
			version      := "0.1.0-SNAPSHOT"
		)),
		name := "Mieke",
		libraryDependencies ++= Seq(
			scalaTest % Test,
			"org.scalafx" %% "scalafx" % "8.0.144-R12"
		)
	)