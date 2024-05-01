<template>
  <div
    class="border-4 rounded-lg py-3 bg-white h-30 px-10 drop-shadow-lg border-soft_green w-full"
  >
    <div>
      <div name="main tag" class="text-md">
        <span>{{ props.typeOfRead }}: </span>
        <span>{{ props.value }} {{ props.measure }}</span>
      </div>
      <img :src="props.src" alt="" />
    </div>
    <hr class="w-full h-2 mt-2" />
    <div name="descripcion" class="text-xs">
      {{ props.description }}
    </div>
  </div>
</template>
<script setup lang="ts">
const props = defineProps<{
  src: string;
  typeOfRead: string;
  value: number;
  description: string;
  measure: string;
}>();
</script>
