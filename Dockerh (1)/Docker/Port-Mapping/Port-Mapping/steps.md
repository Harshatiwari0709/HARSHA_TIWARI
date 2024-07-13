docker build -t cdac-enrollment-app .

docker run -p 5500:5002 -e PORT=5002 cdac-enrollment-app



