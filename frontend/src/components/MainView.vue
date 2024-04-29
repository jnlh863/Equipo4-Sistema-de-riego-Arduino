<template>
  <div class="w-screen h-screen max-h-screen box-border flex flex-col">
    <NavBar />
    <div class="h-full bg-back flex justify-center items-center py-10 px-4">
      <div
        class="bg-almost_white max-w-6xl w-full max-h-full h-full flex flex-col gap-3 rounded-lg px-5 py-10"
      >
        <div class="text-4xl mb-10">Lectura de sensores:</div>
        <div
          class="flex items-center justify-center items-space_bt flex-col gap-10"
        >
          <Container
            :type-of-read="'Temperatura'"
            :src="'../assets/images/thermometer-temperature-svgrepo-com.svg'"
            :value="31"
            :description="descriptionTemp"
            :measure="'Cº'"
          />
          <Container
            :type-of-read="'Humedad en el ambiente'"
            :src="'../assets/images/humidity-svgrepo-com.svg'"
            :value="21"
            :description="descriptionHumAir"
            :measure="'g / m³'"
          />
          <Container
            :type-of-read="'Humedad en la tierra'"
            :src="'../assets/images/humidity-svgrepo-com (1).svg'"
            :value="20"
            :description="descriptionHumSoil"
            :measure="'WFV'"
          />
          <Container
            :type-of-read="'Calidad del aire'"
            :src="'../assets/images/smog-svgrepo-com.svg'"
            :value="10"
            :description="descriptionAirQual"
            :measure="'AQI'"
          />
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import NavBar from "./NavBar.vue";
import { db } from "../firebase.ts";
import { collection, getDocs, setDoc } from "firebase/firestore";
import Container from "./Container.vue";
const humidityAir = ref(25);
const humiditySoil = ref();
const temperature = ref();
const airQuality = ref();
const descriptionTemp = ref(
  "La temperatura es un elemento esencial en el cultivo y desarrollo de las plantas. Junto con los niveles de luz, dióxido de carbono, humedad del aire, agua y nutrientes, la temperatura influye en el crecimiento de la planta y la productividad de las cosechas."
);
const descriptionHumAir = ref(
  "Si la humedad es demasiado baja, con frecuencia el crecimiento de las plantas se verá comprometido, ya que los cultivos tardan más tiempo en obtener un tamaño adecuado para la venta. "
);
const descriptionHumSoil = ref(
  "La determinación de la humedad natural del suelo es primordial para resolver problemas vinculados a las necesidades de agua de riego, consideraciones ambientales y determinación de los excedentes hídricos."
);
const descriptionAirQual = ref(
  "Los efectos de la contaminación atmosférica se pueden manifestar por la alteración de diversos mecanismos vitales de las plantas: las funciones metabólicas y los tejidos se pueden ver afectados por diversos compuestos gaseosos con azufre o flúor."
);
await collection(db, "datos");
await getDocs(collection);
</script>
