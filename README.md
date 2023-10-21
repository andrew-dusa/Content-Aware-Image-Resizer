# Content-Aware-Image-Resizer

## Brief Summary
We use C++ to make a dual-gradient energy function to find a path along the image with the lowest energy to remove. If a path across the image, either vertically or horizontally has the lowest energy, this means it likely does not contain any important edges or information. Using this, we can take an image with dimensions up to 1920x1080 and crop it to a smaller size and shape while retaining important details.
### How to use:
Simply run the program after compiling the project and when prompted give it the path to the .ppm file you want to scale. Then when prompted for the desired dimensions choose what size you want the resulting image to be. The new generated image will be placed in the same directory.


<img width="1075" alt="Screenshot 2023-10-21 at 10 33 39 AM" src="https://github.com/andrew-dusa/Content-Aware-Image-Resizer/assets/93221044/3cf582a0-d04b-4b87-8d74-04e8eeb13fdf">

Notice how this scaled version still includes the whole tree.
<img width="1068" alt="Screenshot 2023-10-21 at 10 34 58 AM" src="https://github.com/andrew-dusa/Content-Aware-Image-Resizer/assets/93221044/eef6c982-512d-4bef-b178-77e211e68c30">

<img width="1073" alt="Screenshot 2023-10-21 at 10 35 25 AM" src="https://github.com/andrew-dusa/Content-Aware-Image-Resizer/assets/93221044/3e97ab9b-beeb-4229-9617-6d05ab4ad12f">

Notice how the birds all the way from the left of the image are included in the cropped and scaled version.
<img width="493" alt="Screenshot 2023-10-21 at 10 36 59 AM" src="https://github.com/andrew-dusa/Content-Aware-Image-Resizer/assets/93221044/c1276ddf-df11-4df8-a34a-cb7cfda99b49">
