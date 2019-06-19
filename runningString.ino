void runningString(){
 display.clearDisplay();
    // устанавливаем цвет текста
    display.setTextColor(display.color565(0, 255, 0));
    // указываем начальную координату вывода текста {textX; 12}
    display.setCursor(textX, 12);
    // выводим текст
    display.print(textStr);
    // сдвигаем текст на один пиксель при каждом выполнении цикла
    textX--;
    delay(5);
    // если был отображён весь текст
    if (textX < textMin) {
      // начинаем выводить текст заново
      textX = display.width();
    }
    // выводим текст из буфера на матрицу
    display.swapBuffers(); 
}

void runningString1() {
display.clearDisplay();
    // устанавливаем цвет текста
    display.setTextColor(display.color565(255, 0, 0));
    // указываем начальную координату вывода текста {textX; 12}
    display.setCursor(textX, 12);
    // выводим текст
    display.print(textStr1);
    // сдвигаем текст на один пиксель при каждом выполнении цикла
    textX--;
    delay(5);
    // если был отображён весь текст
    if (textX < textMin) {
      // начинаем выводить текст заново
      textX = display.width();
    }
    // выводим текст из буфера на матрицу
    display.swapBuffers(); 
}
