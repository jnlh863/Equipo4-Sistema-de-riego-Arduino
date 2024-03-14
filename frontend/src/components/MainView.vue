<template>
  <div class="w-screen h-screen max-h-screen box-border flex flex-col">
    <NavBar />
    <div class="h-full bg-back flex justify-center items-center py-3 px-4">
      <div
        class="bg-almost_white max-w-lg w-full max-h-full h-full rounded-lg p-3"
      >
        <h3>Lectura de sensores:</h3>
        <div class="flex items-center">
          <div>Temperatura del ambiente: {{ humidityAir }} Cº</div>

          <img
            class="h-4 w-4"
            src="../assets/images/thermometer-temperature-svgrepo-com.svg"
            alt="thermo"
          />
        </div>
        <div class="flex items-center">
          <div>Nivel de humedad del tierra:</div>
          <img
            class="h-4 w-4"
            src="../assets/images/humidity-svgrepo-com.svg"
            alt="thermo"
          />
        </div>
        <div class="flex items-center">
          <div>Nivel de humedad del ambiente:</div>
          <img
            class="h-4 w-4"
            src="../assets/images/humidity-svgrepo-com (1).svg"
            alt="thermo"
          />
        </div>
        <div class="flex items-center">
          <div>Calidad del aire:</div>
          <img
            class="h-4 w-4"
            src="../assets/images/smog-svgrepo-com.svg"
            alt="thermo"
          />
        </div>
      </div>
    </div>
  </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import NavBar from "./NavBar.vue";

const humidityAir = ref(25);
const humiditySoil = ref();
const temperature = ref();
const airQuality = ref();
</script>
