<script setup lang="ts">
import { ref, onMounted, onBeforeUnmount } from "vue";
import NavBar from "./NavBar.vue";
import { db } from "../firebase.ts";
import { getDoc, doc, updateDoc } from "firebase/firestore";
import Container from "./Container.vue";
const humidityAir = ref("");
const soilMoisture = ref("");
const temperature = ref("");
const interval = ref();
const newIntervalToBeSet = ref(60);
const descriptionTemp = ref(
  "La temperatura es un elemento esencial en el cultivo y desarrollo de las plantas. Junto con los niveles de luz, dióxido de carbono, humedad del aire, agua y nutrientes, la temperatura influye en el crecimiento de la planta y la productividad de las cosechas."
);
const descriptionHumAir = ref(
  "Si la humedad es demasiado baja, con frecuencia el crecimiento de las plantas se verá comprometido, ya que los cultivos tardan más tiempo en obtener un tamaño adecuado para la venta. "
);
const descriptionHumSoil = ref(
  "La determinación de la humedad natural del suelo es primordial para resolver problemas vinculados a las necesidades de agua de riego, consideraciones ambientales y determinación de los excedentes hídricos."
);

const reloadData = async () => {
  const documentRef = doc(db, "EspData", "ambientquality");
  const data = await getDoc(documentRef);
  if (data.data() === undefined) {
    humidityAir.value = "";
    soilMoisture.value = "";
    temperature.value = "";
  } else {
    humidityAir.value = data.data()!.Humidity;
    soilMoisture.value = data.data()!.SoilMoisture;
    temperature.value = String(Math.round(data.data()!.Temperature));
  }
};
const stopReloadTimer = () => {
  clearInterval(interval.value);
};
const startReloadTimer = () => {
  interval.value = setInterval(() => {
    // Call the method to reload your component data here
    reloadData();
  }, 5000); // 5000 milliseconds = 5 seconds, adjust this according to your needs
};
async function uploadNewInterval() {
  if (newIntervalToBeSet.value < 30)
    alert("El intervalo no puede ser menor a 30 segundos");
  const documentRef = doc(db, "EspData", "intervals");
  await updateDoc(documentRef, {
    interval: newIntervalToBeSet.value * 1000,
    waterPlants: true,
  });
}

async function waterPlants() {
  const documentRef = doc(db, "EspData", "intervals");
  await updateDoc(documentRef, {
    waterPlants: true,
  });
}

onMounted(async () => {
  startReloadTimer();
});

onBeforeUnmount(async () => {
  stopReloadTimer();
});
</script>

<template>
  <div class="max-w-screen h-screen max-h-screen box-border flex flex-col">
    <NavBar />
    <div class="h-full bg-back flex justify-center items-center py-3 px-4">
      <div
        class="bg-almost_white max-w-6xl w-full h-full flex flex-col rounded-lg px-5 py-10"
      >
        <div class="flex space-around items-center justify-around mb-2">
          <div class="text-lg">Lectura de sensores:</div>
          <button
            class="bg-white rounded-lg border-[#7EB09B] border-2 px-2 hover:bg-[#7EB09B] hover:text-white duration-200"
            @click="waterPlants"
          >
            Regar planta
          </button>
          <div class="flex gap-2 justify-center items-center">
            <input
              type="number"
              min="30"
              v-model="newIntervalToBeSet"
              class="w-[60px] h-4 text-[10px] outline-none border-[#D9C5B2] focus:outline-none focus:border-transparent focus:ring-0 border-2 bg-[#F3F3F4] rounded-md p-1"
            />
            <button
              @click="
                async () => {
                  await uploadNewInterval();
                }
              "
              class="outline outline-1 bg-light_yellow font-semibold text-[#403b2f] rounded-md text-slate-400 text-[8px] text-wrap w-12 outline-yellow px-1"
            >
              Establecer intervalo de tiempo
            </button>
          </div>
        </div>

        <div
          class="flex items-center justify-center items-space_bt flex-col gap-3"
        >
          <Container
            :type-of-read="'Temperatura'"
            :src="'../assets/images/thermometer-temperature-svgrepo-com.svg'"
            :value="temperature"
            :description="descriptionTemp"
            :measure="'Cº'"
          />
          <Container
            :type-of-read="'Humedad en el ambiente'"
            :src="'../assets/images/humidity-svgrepo-com.svg'"
            :value="humidityAir"
            :description="descriptionHumAir"
            :measure="'g / m³'"
          />
          <Container
            :type-of-read="'Humedad en la tierra'"
            :src="'../assets/images/humidity-svgrepo-com (1).svg'"
            :value="soilMoisture"
            :description="descriptionHumSoil"
            :measure="'WFV'"
          />
        </div>
      </div>
    </div>
  </div>
</template>
