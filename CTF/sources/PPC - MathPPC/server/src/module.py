import random

# Функция для генерации математического выражения
def generate_math_expression():
	num1 = random.randint(100, 9999)
	num2 = random.randint(100, 9999)
	operation = random.choice(["+", "-", "*", "//"])
	return f"{num1} {operation} {num2}"
