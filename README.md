# Examen Contenedores y Orquestadores

El proyecto consiste en una aplicación web en C, empaquetada en Docker y desplegada en Kubernetes. El servidor web escucha en el puerto 8080 y responde con un mensaje básico. Se utiliza un archivo "Dockerfile" para construir el contenedor y tres archivos de configuración de Kubernetes ("deployment.yaml", "service.yaml" e "ingress.yaml") para su despliegue en el clúster. El Ingress permite acceder a la aplicación mediante diferentes rutas.
