# 3DViewer

## Описание

- Высокопроизводительный 3D рендерер на C++17, Qt6 и MVC, поддерживающий .obj файлы.

## Цель

- Эффективная визуализация 3D моделей с возможностью трансформации и кастомизации.

## Архитектура

- MVC (Model, View, Controller)
- Паттерны
  - Facade (Manipulation)
  - Strategy (Parser, Affine Transformations)
  - Singleton (Controller)

## Требования

- C++17
- Qt6.

## Установка (macOS)

1. `git clone <repository_url>`
2. `cd 3D Viewer_v2.0/src`
3. `make`
4. `open ./3D Viewer/3d Viewer.app`

## Функциональность

- Загрузка .obj
- Аффинные трансформации
  - Перенос
  - Вращение
  - Масштабирование
- Настройка внешнего вида
  - Линии
  - Вершины
  - Цвет
  - Проекция
- Экспорт в BMP/JPEG
- Создание GIF анимаций
- Сохранение настроек
- Юнит-тесты
- Google C++ Style Guide.

## Скриншоты и GIF

- Интерфейс доступен после выбора корректной модели через кнопку `Choose File`:
  ![img_1][img_1]
- Также, возможно сохранить скриншот в любую выбранную папку:
  ![img_2][img_2] \
  *Окно после сохранения* \
  ![img_3][img_3] \
  *Сделанный скриншот*
- После нажатия на кнопку `GIF`, будут записаны любые манипуляции с моделью
  ![img_4][img_4] \
  *Окно появится после записи* \
  ![img_5][img_5] \
  *Результат записанных манипуляций в `GIF`*

[img_1]: images/img_1.png
[img_2]: images/img_2.png
[img_3]: images/cubecarcas.jpg
[img_4]: images/img_3.png
[img_5]: images/cubecarcas.gif

## Авторы

Анастасия([@nanali96](https://t.me/nanali96)), Касим([@Sckroll](https://t.me/Sckroll)), Эмилия([@liaaemi](https://t.me/liaaemi))
