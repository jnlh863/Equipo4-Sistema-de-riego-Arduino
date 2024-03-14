import typography from "@tailwindcss/typography";
import forms from "@tailwindcss/forms";
import aspectRatio from "@tailwindcss/aspect-ratio";

/** @type {import('tailwindcss').Config} */
export default {
  content: ["./index.html", "./src/**/*.{vue,js,ts,jsx,tsx}"],
  theme: {
    colors: {
      back: "#e6f0da",
      strong_green: "#007F73",
      soft_green: "#4CCD99",
      yellow: "#FFC700",
      light_yellow: "#FFF455",
      almost_white: "#f7faf0",
      white: "#ffffff",
    },
    extend: {},
  },
  plugins: [typography, forms, aspectRatio],
};
